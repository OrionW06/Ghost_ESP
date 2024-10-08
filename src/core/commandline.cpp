#include "commandline.h"
#include "../components/wifi_module/Controllers/AppController.h"
#include "../components/wifi_module/Controllers/YoutubeController.h"
#include "../components/wifi_module/Controllers/NetflixController.h"
#include "../components/wifi_module/Controllers/RokuController.h"
#include "../components/ble_module/ble_module.h"
#include <components/wifi_module/Features/Dial.h>
#include "../components/wifi_module/Features/DeauthDetector.h"
#include <components/wifi_module/Features/ESPmDNSHelper.h>
#include <components/gps_module/gps_module.h>

CommandLine::CommandLine() {
}

void CommandLine::RunSetup() {
  Serial.println(F("         Ghost ESP     \n"));
  Serial.println(F("       By: Spooky\n"));
  LOG_MESSAGE_TO_SD(F("         Ghost ESP     \n"));
  LOG_MESSAGE_TO_SD(F("       By: Spooky\n"));
}

String CommandLine::getSerialInput() {
  String input = "";

  if (Serial.available() > 0)
  {
    input = Serial.readStringUntil('\n');

    input.trim();
    Serial.println(input);
  }
   
  return input;
}

void CommandLine::main(uint32_t currentTime) {
  String input = this->getSerialInput();

  this->runCommand(input);

  if (input != "")
    Serial.print("> ");
}

LinkedList<String> CommandLine::parseCommand(String input, char* delim) {
  LinkedList<String> cmd_args;

  bool inQuote = false;
  bool inApostrophe = false;
  String buffer = "";

  for (int i = 0; i < input.length(); i++) {
    char c = input.charAt(i);

    if (c == '"') {
      // Check if the quote is within an apostrophe
      if (inApostrophe) {
        buffer += c;
      } else {
        inQuote = !inQuote;
      }
    } else if (c == '\'') {
      // Check if the apostrophe is within a quote
      if (inQuote) {
        buffer += c;
      } else {
        inApostrophe = !inApostrophe;
      }
    } else if (!inQuote && !inApostrophe && strchr(delim, c) != NULL) {
      cmd_args.add(buffer);
      buffer = "";
    } else {
      buffer += c;
    }
  }

  // Add the last argument
  if (!buffer.isEmpty()) {
    cmd_args.add(buffer);
  }

  return cmd_args;
}

int CommandLine::argSearch(LinkedList<String>* cmd_args_list, String key) {
  for (int i = 0; i < cmd_args_list->size(); i++) {
    if (cmd_args_list->get(i) == key)
      return i;
  }

  return -1;
}

bool CommandLine::checkValueExists(LinkedList<String>* cmd_args_list, int index) {
  if (index < cmd_args_list->size() - 1)
    return true;
    
  return false;
}

bool CommandLine::inRange(int max, int index) {
  if ((index >= 0) && (index < max))
    return true;

  return false;
}


bool CommandLine::hasSSIDs() {
  if (ssids->size() == 0)
    return false;

  return true;
}

String CommandLine::toLowerCase(String str) {
  String result = str;
  for (int i = 0; i < str.length(); i++) {
    int charValue = str.charAt(i);
    if (charValue >= 65 && charValue <= 90) { // ASCII codes for uppercase letters
      charValue += 32;
      result.setCharAt(i, char(charValue));
    }
  }
  return result;
}


void CommandLine::runCommand(String input)
{
    if (input == "") 
    {
        return;
    }

    LinkedList<String> cmd_args = this->parseCommand(input, " ");
    

    if (cmd_args.get(0) == F("blespam"))
    {
      #ifdef HAS_BT
      int bt_type_sw = this->argSearch(&cmd_args, "-t");
      if (bt_type_sw != -1) {
        String bt_type = cmd_args.get(bt_type_sw + 1);
        if (bt_type == F("apple")) {
          Serial.println("Starting Sour Apple attack. Stop with " + (String)"stopscan");
          LOG_MESSAGE_TO_SD(F("Starting Sour Apple attack."));
          SystemManager::getInstance().bleModule->executeSpam(Apple, true);
          return;
        }

        if (bt_type == F("windows")) {
          Serial.println("Starting Swiftpair Spam attack. Stop with " + (String)"stopscan");
          LOG_MESSAGE_TO_SD(F("Starting Swiftpair Spam attack."));
          SystemManager::getInstance().bleModule->executeSpam(Microsoft, true);
          return;
        }

        if (bt_type == F("samsung")) {
          Serial.println("Starting Samsung Spam attack. Stop with " + (String)"stopscan");
          LOG_MESSAGE_TO_SD(F("Starting Samsung Spam attack."));
          SystemManager::getInstance().bleModule->executeSpam(Samsung, true);
          return;
        }

        if (bt_type == F("google")) {
          Serial.println("Starting Google Spam attack. Stop with " + (String)"stopscan");
          LOG_MESSAGE_TO_SD(F("Starting Google Spam attack."));
          SystemManager::getInstance().bleModule->executeSpam(Google, true);
          return;
        }

        if (bt_type == F("all"))
        {
          Serial.println("Starting Spam all attack. Stop with " + (String)"stopscan");
          LOG_MESSAGE_TO_SD(F("Starting random wifi beacon attack."));
          SystemManager::getInstance().bleModule->executeSpamAll();
        }
      }
      #endif
    }

    if (cmd_args.get(0) == F("attack"))
    {
      int wifi_type_sw = this->argSearch(&cmd_args, "-t");

      if (wifi_type_sw != -1) {
        String attack_type = cmd_args.get(wifi_type_sw + 1);

        if (attack_type == F("beacon"))
        {
          int israndom = this->argSearch(&cmd_args, "-r");
          int islist = this->argSearch(&cmd_args, "-l");

          if (israndom != -1)
          {
            Serial.println("Starting random wifi beacon attack. Stop with " + (String)"stopscan");
            LOG_MESSAGE_TO_SD(F("Starting random wifi beacon attack."));
            SystemManager::getInstance().wifiModule.RunSetup();
            SystemManager::getInstance().wifiModule.Attack(AT_RandomSSID);
            return;
          }

          if (islist != -1)
          {
            if (ssids->size() > 0)
            {
              Serial.println("Starting random wifi list attack. Stop with " + (String)"stopscan");
              LOG_MESSAGE_TO_SD(F("Starting random wifi list attack."));
              SystemManager::getInstance().wifiModule.RunSetup();
              SystemManager::getInstance().wifiModule.Attack(AT_ListSSID);
            }
            else 
            {
              Serial.println(F("Add Some SSIDs..."));
              LOG_MESSAGE_TO_SD(F("Add Some SSIDs..."));
            }
            return;
          }
        }

        if(attack_type == F("deauth")){
          bool IsSelected =  SelectedAP.channel != 0;
          if (IsSelected)
          {
            Serial.println("Starting Deauth attack. Stop with " + (String)"stopscan");
            LOG_MESSAGE_TO_SD(F("Starting Deauth attack."));
            SystemManager::getInstance().wifiModule.RunSetup();
            SystemManager::getInstance().wifiModule.Attack(AT_DeauthAP);
          }
          else 
          {
            Serial.println(F("Scan for Access Points First..."));
            LOG_MESSAGE_TO_SD(F("Scan for Access Points First..."));
          }
          return;
        }

        if (attack_type == F("rickroll"))
        {
          Serial.println("Starting Rickroll wifi beacon attack. Stop with " + (String)"stopscan");
          LOG_MESSAGE_TO_SD(F("Starting Rickroll wifi beacon attack."));
          SystemManager::getInstance().wifiModule.RunSetup();
          SystemManager::getInstance().wifiModule.Attack(AT_Rickroll);
          return;
        }

        if (attack_type == F("wps_pwn"))
        {
          Serial.println("Starting wps_pwn wifi attack. Stop with " + (String)"stopscan");
          LOG_MESSAGE_TO_SD(F("Starting wps_pwn beacon attack."));
          SystemManager::getInstance().wifiModule.RunSetup();
          SystemManager::getInstance().wifiModule.Attack(AT_WPS);
        }

        if (attack_type == F("karma"))
        {
          Serial.println("Starting Karma wifi beacon attack. Stop with " + (String)"stopscan");
          LOG_MESSAGE_TO_SD(F("Starting Karma wifi beacon attack."));
          SystemManager::getInstance().wifiModule.RunSetup();
          SystemManager::getInstance().wifiModule.Attack(AT_Karma);
        }
      }
    }

    if (cmd_args.get(0) == F("findtheflippers"))
    {
      #ifdef HAS_BT
      SystemManager::getInstance().bleModule->findtheflippers();
      #endif
    }

    if (cmd_args.get(0) == F("airtagscan"))
    {
      #ifdef HAS_BT
      SystemManager::getInstance().bleModule->AirTagScanner();
      #endif
    }
    
    if (cmd_args.get(0) == F("detectblespam"))
    {
      #ifdef HAS_BT
      SystemManager::getInstance().bleModule->BleSpamDetector();
      #endif
    }

    if (cmd_args.get(0) == F("sniffbt"))
    {
      #ifdef HAS_BT
      SystemManager::getInstance().bleModule->BleSniff();
      #endif
    }



    if (cmd_args.get(0) == F("scanap"))
    {
      Serial.println("Starting to scan access points");
      LOG_MESSAGE_TO_SD("Starting to scan access points");
      SystemManager::getInstance().wifiModule.Scan(SCAN_AP);
      return;
    }

    if (cmd_args.get(0) == F("setsetting"))
    {
      int settingindex = this->argSearch(&cmd_args, "-i");
      int settingvalue = this->argSearch(&cmd_args, "-v");

      if (settingindex != -1 && settingvalue != -1)
      {
        String settingindexString = cmd_args.get(settingindex + 1);
        String settingvalueString = cmd_args.get(settingvalue + 1);

        int ActualSettingsIndex = settingindexString.toInt();
        int ActualSettingsValue = settingvalueString.toInt();

        if (ActualSettingsIndex == 1) // RGB Mode
        {
          switch (ActualSettingsValue)
          {
            case 1:
            {
              SystemManager::getInstance().Settings.setRGBMode(FSettings::RGBMode::Stealth);
              break;
            }
            case 2:
            {
              SystemManager::getInstance().Settings.setRGBMode(FSettings::RGBMode::Normal);
              break;
            }
            case 3:
            {
              SystemManager::getInstance().Settings.setRGBMode(FSettings::RGBMode::Rainbow);
              break;
            }
          }
        }

        if (ActualSettingsIndex == 2)
        {
          switch (ActualSettingsValue)
          {
            case 1:
            {
              SystemManager::getInstance().Settings.setChannelSwitchDelay(0.5);
              break;
            }
            case 2:
            {
              SystemManager::getInstance().Settings.setChannelSwitchDelay(1);
              break;
            }
            case 3:
            {
              SystemManager::getInstance().Settings.setChannelSwitchDelay(2);
              break;
            }
            case 4:
            {
              SystemManager::getInstance().Settings.setChannelSwitchDelay(3);
              break;
            }
            case 5:
            {
              SystemManager::getInstance().Settings.setChannelSwitchDelay(4);
              break;
            }
          }
        }

        if (ActualSettingsIndex == 3)
        {
          switch (ActualSettingsValue)
          {
            case 1:
            {
              SystemManager::getInstance().Settings.setChannelHoppingEnabled(false);
              break;
            }
            case 2:
            {
              SystemManager::getInstance().Settings.setChannelHoppingEnabled(true);
              break;
            }
          }
        }

        if (ActualSettingsIndex == 4)
        {
          switch (ActualSettingsValue)
          {
            case 1:
            {
              SystemManager::getInstance().Settings.SetRandomBLEMacEnabled(false);
              break;
            }
            case 2:
            {
              SystemManager::getInstance().Settings.SetRandomBLEMacEnabled(true);
              break;
            }
          }
        }

      }
      return;
    }

    if (cmd_args.get(0) == F("castv2connect"))
    {
      HasRanCommand = true;
      int ssid = this->argSearch(&cmd_args, "-s");
      int password = this->argSearch(&cmd_args, "-p");
      int value = this->argSearch(&cmd_args, "-v");

      if (ssid != -1 && password != -1)
      {
        String SSID = cmd_args.get(ssid + 1);
        String Password = cmd_args.get(password + 1);
        if (value != -1)
        {
          String Value = cmd_args.get(value + 1);
          ESPmDNSHelper* helper = new ESPmDNSHelper(SSID.c_str(), Password.c_str(), "", Value.c_str(), "233637DE");
        }
      }
    }

    if (cmd_args.get(0) == F("streetdetector"))
    {
      #ifdef HAS_GPS
      SystemManager::getInstance().gpsModule->setup();
      
      while (!SystemManager::getInstance().gpsModule->Stop)
      {
        SystemManager::getInstance().gpsModule->streetloop();
      }
      #endif
    }

    if (cmd_args.get(0) == F("wardrive"))
    {
      int EnableBLE = this->argSearch(&cmd_args, "-b");

      #ifdef HAS_GPS
      SystemManager::getInstance().wifiModule.EnableBLEWardriving = EnableBLE != -1;
      SystemManager::getInstance().wifiModule.Scan(ScanType::SCAN_WARDRIVE);
      #endif
    }

    if (cmd_args.get(0) == F("sendwebrequest"))
    {
      int SSID = this->argSearch(&cmd_args, "-s");
      int Password = this->argSearch(&cmd_args, "-p");
      int type = this->argSearch(&cmd_args, "-t");
      int Url = this->argSearch(&cmd_args, "-u");
      int Payload = this->argSearch(&cmd_args, "-l");

      if (SSID == -1 || Password == -1)
      {
        Serial.println("Empty Wifi Name or Password");
        return;
      }

      if (type != -1 && Url != -1)
      {
        String SSIDString = cmd_args.get(SSID + 1);
        String PasswordString = cmd_args.get(Password + 1);
        String TypeString = cmd_args.get(type + 1);
        String UrlString = cmd_args.get(Url + 1);

        if (Payload != -1)
        {
          String PayloadString = cmd_args.get(Payload + 1);
          SystemManager::getInstance().wifiModule.SendWebRequest(SSIDString.c_str(), PasswordString.c_str(), TypeString, UrlString, PayloadString);
        }
        else 
        {
          SystemManager::getInstance().wifiModule.SendWebRequest(SSIDString.c_str(), PasswordString.c_str(), TypeString, UrlString);
        }
      }
    }

    if (cmd_args.get(0) == F("deauthdetector"))
    {
      HasRanCommand = true;
      int ssid = this->argSearch(&cmd_args, "-s");
      int password = this->argSearch(&cmd_args, "-p");
      int webhook = this->argSearch(&cmd_args, "-w");
      int channel_index = this->argSearch(&cmd_args, "-c");

      String SSID;
      String Password;
      String WebHook;
      String channel;
      if (ssid != -1 && password != -1)
      {
        SSID = cmd_args.get(ssid + 1);
        Password = cmd_args.get(password + 1);

        if (webhook != -1)
        {
          WebHook = cmd_args.get(webhook + 1);
        }
      }

      if (channel_index != -1)
      {
        channel = cmd_args.get(channel_index + 1);
      }
      InitDeauthDetector(channel, SSID, Password, WebHook);
    }

    if (cmd_args.get(0) == F("dialconnect"))
    {
      HasRanCommand = true;
      int ssid = this->argSearch(&cmd_args, "-s");
      int password = this->argSearch(&cmd_args, "-p");
      int type = this->argSearch(&cmd_args, "-t");
      int value = this->argSearch(&cmd_args, "-v");

      if (ssid != -1 && password != -1)
      {
        String SSID = cmd_args.get(ssid + 1);
        String Password = cmd_args.get(password + 1);
        if (type != -1 && value != -1)
        {
          String Type = cmd_args.get(type + 1);
          String Value = cmd_args.get(value + 1);
          AppController* controller = nullptr;
          if (Type.startsWith(F("youtube")))
          {
            controller = new YoutubeController();
          }
          else if (Type.startsWith(F("roku")))
          {
            controller = new RokuController();
          }
          else if (Type.startsWith(F("netflix")))
          {
            controller = new NetflixController();
          }
          else 
          {
            Serial.println(F("Type is Invalid...."));
            LOG_MESSAGE_TO_SD(F("Type is Invalid...."));
            return;
          }

          DIALClient* dial = new DIALClient(Value.c_str(), SSID.c_str(), Password.c_str(), controller);
#ifdef OLD_LED
SystemManager::getInstance().rgbModule->setColor(LOW, HIGH, LOW);
#endif
#ifdef NEOPIXEL_PIN
SystemManager::getInstance().neopixelModule->setColor(SystemManager::getInstance().neopixelModule->strip.Color(255, 0, 0));
#endif
          dial->Execute();
          delete dial;
          delete controller;
          return;
        }
        else 
        {
          Serial.println(F("Please Select a Type Of Dial Attack to Perform..."));
          LOG_MESSAGE_TO_SD(F("Please Select a Type Of Dial Attack to Perform..."));
        }
      }
      else 
      {
        Serial.println(F("SSID and Password are Empty..."));
        LOG_MESSAGE_TO_SD(F("SSID and Password are Empty..."));
      }
    }

    if (cmd_args.get(0) == F("scansta"))
    {
      if (access_points->size() > 0)
      {
        Serial.println(F("Starting to scan stations"));
        LOG_MESSAGE_TO_SD(F("Starting to scan stations"));
        SystemManager::getInstance().wifiModule.Scan(SCAN_STA);
      }
      else 
      {
        Serial.println(F("Please Scan For a Access Point First"));
        LOG_MESSAGE_TO_SD(F("Please Scan For a Access Point First"));
      }
      
      return;
    }

    if (cmd_args.get(0) == F("calibrate"))
    {
      SystemManager::getInstance().wifiModule.Calibrate();
    }

    if (cmd_args.get(0) == F("ssid"))
    {
      int ap_sw = this->argSearch(&cmd_args, "-a");
      int ss_sw = this->argSearch(&cmd_args, "-g");
      int nn_sw = this->argSearch(&cmd_args, "-n");

      if (ap_sw != -1 && ss_sw != -1)
      {
        String NumSSids = cmd_args.get(ss_sw + 1);
        NumSSids.trim();
        SystemManager::getInstance().wifiModule.generateSSIDs(NumSSids.toInt());
        Serial.printf("%i Random Ssids Generated\n", NumSSids.toInt());
        LOG_MESSAGE_TO_SD(F("Random Ssids Generated\n"));
        LOG_MESSAGE_TO_SD(String(NumSSids.toInt()).c_str());
      }

      if (ap_sw != -1 && nn_sw != -1)
      {
        String SSIDName = cmd_args.get(nn_sw + 1);
        SSIDName.trim();
        SystemManager::getInstance().wifiModule.addSSID(SSIDName);
        Serial.println("Added SSID " + SSIDName);
        LOG_MESSAGE_TO_SD(F("Added SSID "));
        LOG_MESSAGE_TO_SD(SSIDName.c_str());
      }
    }

    if (cmd_args.get(0) == "help")
    {
      Serial.println(F("HELP MENU:"));
      Serial.println(F("- 'scanap': Scan for WiFi Access Points."));
      Serial.println(F("- 'scansta': Scan for WiFi Stations."));
      Serial.println(F("- 'list -a': List all Access Points."));
      Serial.println(F("- 'list -c': List all WiFi Clients."));
      Serial.println(F("- 'select -a <index>': Select an Access Point by index."));
      Serial.println(F("- 'select -s <index>': Select a Station by index."));
      Serial.println(F("- 'ssid -a -g': Generate and add a random SSID."));
      Serial.println(F("- 'ssid -a -n <SSID>': Add a specific SSID."));
      Serial.println(F("- 'attack -t beacon -l': Start Beacon Spam with SSID List."));
      Serial.println(F("- 'attack -t beacon -r': Start Beacon Spam with Random SSIDs."));
      Serial.println(F("- 'attack -t karma': Start Beacon Spam with Known SSIDs."));
      Serial.println(F("- 'attack -t rickroll': Start Rickroll Beacon Spam."));
      Serial.println(F("- 'attack -t deauth': Start Deauth Attack on the Captured Networks"));
      Serial.println(F("- 'castv2connect -s <SSID> -p <PASSWORD> -v <Device>': Connect to a device using CastV2 protocol."));
      Serial.println(F("- 'dialconnect -s <SSID> -p <PASSWORD> -t <App> -v <Device>': Connect to a device using DIAL protocol."));
      Serial.println(F("- 'deauthdetector -s <SSID> -p <PASSWORD> -w <WebHookUrl>': Detect deauthentication frames."));
      Serial.println(F("- 'calibrate': Calibrate the most active network. Used for sniffing functions"));
      Serial.println(F("- 'blespam -t <type>': Start BLE spamming of a specific type ('samsung', 'apple', 'google', 'windows', or 'all')."));
      Serial.println(F("- 'sniffraw': Sniff raw WiFi packets."));
      Serial.println(F("- 'sniffbeacon': Sniff WiFi beacons."));
      Serial.println(F("- 'sniffprobe': Sniff WiFi probe requests."));
      Serial.println(F("- 'sniffpwn': Sniff for pwnagotchis in the air."));
      Serial.println(F("- 'sniffdeauth': deauthenticate access points when scanning for them"));
      Serial.println(F("- 'sniffpmkid [-c <channel>]': Sniff for PMKID packets with optional flags for channel"));
      Serial.println(F("- 'findtheflippers': Detect for Flipper Zeros In Your Area"));
      Serial.println(F("- 'detectblespam': Detect BLE Spams That Might Be Happening Around You"));
      Serial.println(F("- 'airtagscan': Detect Apple AirTags and there Payloads around You"));
      Serial.println(F("- 'streetdetector': Detect What Street Your on Using GPS (Requires SD Card With Map Data)"));
      Serial.println(F("- 'wardrive [-b EnableBLEScanning (May Crash After a while if enabled)]': Detect What Street Access Points Are on and gather other WiFi Information"));
    }

    if (cmd_args.get(0) == F("sniffdeauth"))
    {
      int nn_sw = this->argSearch(&cmd_args, "-c");

      if (nn_sw != -1)
      {
        int TargetChannel = cmd_args.get(nn_sw + 1).toInt();
        Serial.println(F("Starting PMKID sniff. Stop with stop scan"));
        SystemManager::getInstance().wifiModule.Sniff(ST_Deauth, TargetChannel);
        return;
      }

      Serial.println(F("Starting PMKID sniff. Stop with stop scan"));
      SystemManager::getInstance().wifiModule.Sniff(ST_Deauth, 0);
    }

    if (cmd_args.get(0) == F("sniffpmkid"))
    {

      int nn_sw = this->argSearch(&cmd_args, "-c");

      if (nn_sw != -1)
      {
        int TargetChannel = cmd_args.get(nn_sw + 1).toInt();
        Serial.println(F("Starting PMKID sniff. Stop with stop scan"));
        SystemManager::getInstance().wifiModule.Sniff(ST_pmkid, TargetChannel);
        return;
      }

      Serial.println(F("Starting PMKID sniff. Stop with stop scan"));
      SystemManager::getInstance().wifiModule.Sniff(ST_pmkid, 0);
    }

    if (cmd_args.get(0) == F("sniffraw"))
    {

      int nn_sw = this->argSearch(&cmd_args, "-c");

      if (nn_sw != -1)
      {
        int TargetChannel = cmd_args.get(nn_sw + 1).toInt();
        Serial.println(F("Starting RAW sniff. Stop with stop scan"));
        SystemManager::getInstance().wifiModule.Sniff(ST_raw, TargetChannel);
        return;
      }

      Serial.println(F("Starting RAW sniff. Stop with stop scan"));
      SystemManager::getInstance().wifiModule.Sniff(ST_raw, 0);
    }

    if (cmd_args.get(0) == F("sniffbeacon"))
    {

      int nn_sw = this->argSearch(&cmd_args, "-c");

      if (nn_sw != -1)
      {
        int TargetChannel = cmd_args.get(nn_sw + 1).toInt();
        Serial.println(F("Starting Beacon sniff. Stop with stop scan"));
        SystemManager::getInstance().wifiModule.Sniff(ST_beacon, TargetChannel);
        return;
      }

      Serial.println(F("Starting Beacon sniff. Stop with stop scan"));
      SystemManager::getInstance().wifiModule.Sniff(ST_beacon, 0);
    }

    if (cmd_args.get(0) == F("sniffprobe"))
    {

      int nn_sw = this->argSearch(&cmd_args, "-c");

      if (nn_sw != -1)
      {
        int TargetChannel = cmd_args.get(nn_sw + 1).toInt();
        Serial.println(F("Starting PROBE sniff. Stop with stop scan"));
        SystemManager::getInstance().wifiModule.Sniff(ST_probe, TargetChannel);
        return;
      }

      Serial.println(F("Starting PROBE sniff. Stop with stop scan"));
      SystemManager::getInstance().wifiModule.Sniff(ST_probe, 0);
    }

    if (cmd_args.get(0) == F("sniffpwn"))
    {

      int nn_sw = this->argSearch(&cmd_args, "-c");

      if (nn_sw != -1)
      {
        int TargetChannel = cmd_args.get(nn_sw + 1).toInt();
        Serial.println(F("Starting PWN sniff. Stop with stop scan"));
        SystemManager::getInstance().wifiModule.Sniff(ST_pwn, TargetChannel);
        return;
      }

      Serial.println(F("Starting PWN sniff. Stop with stop scan"));
      SystemManager::getInstance().wifiModule.Sniff(ST_pwn, 0);
    }


    if (cmd_args.get(0) == F("select"))
    {
      int ap_sw = this->argSearch(&cmd_args, "-a");
      int SSIDIndex = cmd_args.get(ap_sw + 1).toInt();
      int ssid_sw = this->argSearch(&cmd_args, "-s");
      String SSIDArg = cmd_args.get(ssid_sw + 1);
      bool Selected = false;

      for (int i = 0; i < access_points->size(); i++) {
        AccessPoint AP = access_points->get(i);

        if (SSIDIndex != -1 && i == SSIDIndex)
        {
          SelectedAP = AP;
          Selected = true;
          break;
        }

        if (ssid_sw != -1 && AP.essid == SSIDArg)
        {
          SelectedAP = AP;
          Selected = true;
          break;
        }
      }
      if (!Selected)
      {
        Serial.println(F("Did not Select Anything Possible Index out of range"));
        LOG_MESSAGE_TO_SD(F("Did not Select Anything Possible Index out of range"));
      }
      else 
      {
        Serial.println(F("Successfully Selected The Access Point"));
        LOG_MESSAGE_TO_SD(F("Successfully Selected The Access Point"));
      }
    }

    if (cmd_args.get(0) == F("clearlist"))
    {
      int ap_sw = this->argSearch(&cmd_args, "-a");
      int ss_sw = this->argSearch(&cmd_args, "-s");
      int cl_sw = this->argSearch(&cmd_args, "-c");

      if (ap_sw != -1)
      {
        SystemManager::getInstance().wifiModule.ClearList(ClearType::CT_AP);
        Serial.println(F("Cleared Access Point List"));
        LOG_MESSAGE_TO_SD(F("Cleared Access Point List"));
      }
      else if (ss_sw != -1)
      {
        SystemManager::getInstance().wifiModule.ClearList(ClearType::CT_SSID);
        Serial.println(F("Cleared SSID List"));
        LOG_MESSAGE_TO_SD(F("Cleared SSID List"));
      }
      else if (cl_sw != -1)
      {
        SystemManager::getInstance().wifiModule.ClearList(ClearType::CT_STA);
        Serial.println(F("Cleared Station List"));
        LOG_MESSAGE_TO_SD(F("Cleared Station List"));
      }
    }



    if (cmd_args.get(0) == F("list")) {
        int ap_sw = this->argSearch(&cmd_args, "-a");
        int ss_sw = this->argSearch(&cmd_args, "-s");
        int cl_sw = this->argSearch(&cmd_args, "-c");

        if (ap_sw != -1) {
           SystemManager::getInstance().wifiModule.listAccessPoints();
        } else if (ss_sw != -1) {
            SystemManager::getInstance().wifiModule.listSSIDs();
        } else if (cl_sw != -1) {
            SystemManager::getInstance().wifiModule.listStations();
        } else {
            Serial.println(F("You did not specify which list to show"));
            LOG_MESSAGE_TO_SD(F("You did not specify which list to show"));
            return;
        }
    }
  
  
  if (cmd_args.get(0) == F("stop"))
  {
    #ifdef OLD_LED
    SystemManager::getInstance().rgbModule->setColor(1, 1, 1);
    #endif
    #ifdef NEOPIXEL_PIN
    SystemManager::getInstance().neopixelModule->strip.setBrightness(0);
    #endif
    SystemManager::getInstance().wifiModule.shutdownWiFi();
    #ifdef HAS_BT
    SystemManager::getInstance().bleModule->shutdownBLE();
    #endif
  }
}