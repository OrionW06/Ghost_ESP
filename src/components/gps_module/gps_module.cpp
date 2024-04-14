#include "gps_module.h"

String gps_module::findClosestStreet(double lat, double lng) {
    String filename = "/mapdata/streets.csv";

    if (!MapData || !MapData.name() || String(MapData.name()) != filename) {
        if (MapData) {
            MapData.close();
        }
        MapData = SystemManager::getInstance().sdCardModule.readFile(filename.c_str());
        if (!MapData) {
            Serial.println("Cannot open file: " + filename);
            return "";
        }
    }

    MapData.seek(0);

    String closestStreet;
    double minDistance = 999999999;
    MapData.readStringUntil('\n'); // Skip the header line
    while (MapData.available()) {
        String line = MapData.readStringUntil('\n');
        int firstComma = line.indexOf(',');
        int secondComma = line.indexOf(',', firstComma + 1);
        int thirdComma = line.indexOf(',', secondComma + 1);
        int fourthComma = line.indexOf(',', thirdComma + 1);
        int fifthComma = line.indexOf(',', fourthComma + 1);

        double streetLat = line.substring(fourthComma + 1, fifthComma).toDouble();
        double streetLng = line.substring(fifthComma + 1).toDouble();
        String streetName = line.substring(secondComma + 1, thirdComma);

        double distance = calculateDistance(lat, lng, streetLat, streetLng);

        if (distance < minDistance) {
            minDistance = distance;
            closestStreet = streetName;
        }
    }
    return closestStreet;
}

double gps_module::calculateDistance(double lat1, double lon1, double lat2, double lon2)
{
    const double EARTH_RADIUS_KM = 6371.0;

    double lat1Rad = degToRad(lat1);
    double lon1Rad = degToRad(lon1);
    double lat2Rad = degToRad(lat2);
    double lon2Rad = degToRad(lon2);

    double deltaLat = lat2Rad - lat1Rad;
    double deltaLon = lon2Rad - lon1Rad;

    double a = sin(deltaLat / 2) * sin(deltaLat / 2) +
                cos(lat1Rad) * cos(lat2Rad) *
                sin(deltaLon / 2) * sin(deltaLon / 2);

    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return EARTH_RADIUS_KM * c;
}

double gps_module::degToRad(double degrees) {
  return degrees * (M_PI / 180);
}

void gps_module::streetloop() 
{
#ifdef HAS_GPS
  while (Serial2.available() > 0 && !Stop) 
  {
    char c = Serial2.read();

    gps.encode(c);
#endif

    if (Serial.available() > 0)
    {
      Stop = true;
    }

  
    unsigned long currentMillis = millis();
    if (currentMillis - lastUpdate >= updateInterval) {
        lastUpdate = currentMillis;

#ifdef HAS_GPS
      if (gps.location.isValid() && gps.location.isUpdated()) {
        String streetName = findClosestStreet(gps.location.lat(), gps.location.lng());
        Serial.print("Latitude: "); Serial.println(gps.location.lat(), 6);
        Serial.print("Longitude: "); Serial.println(gps.location.lng(), 6);
        Serial.print("Satellites: "); Serial.println(gps.satellites.value());
        Serial.print("Altitude: "); Serial.println(gps.altitude.kilometers());
        Serial.print("Speed: "); Serial.println(gps.speed.kmph());
        Serial.println(streetName);
        LOG_RESULTS("streets.txt", "gps", "Visited " + streetName);
      } else {
        Serial.println("GPS signal not found");
      }
#endif
    }
#ifdef HAS_GPS
  }
#endif
}

void gps_module::setup()
{
    if (SystemManager::getInstance().sdCardModule.Initlized)
    {
#ifdef HAS_GPS
    Serial2.begin(9600, SERIAL_8N1, GPS_TX, GPS_RX);
#endif
    Initilized = true;
    Stop = false;
    Serial.println("Initilized GPS Serial");
    }
    else 
    {
      Initilized = false;
      Stop = true;
      Serial.println("Failed to Initilize GPS Serial Possible SD Card Init Failure");
    }
}