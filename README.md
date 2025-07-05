# ESP32 Marauder
<b>A fork for the ESP32-S3-Mini dev board (16MB flash, 8MB PSRAM on external IC's)</b>

## ESP32 Marauder v1.2.0 Release Notes

### New Features

#### Marauder v7 Hardware Support
- Added official support for Marauder v7 hardware
- Updated TFT display configurations for better compatibility
- Enhanced build system to handle multiple hardware variants

#### Build System Improvements
- Updated GitHub Actions workflow for new screen configurations
- Added support for additional TFT display variants
- Improved build process for different hardware targets

### Bug Fixes
- Fixed display initialization for various hardware configurations
- Improved compatibility with different TFT display modules
- Resolved build issues with specific hardware combinations

---

## ESP32 Marauder v1.1.0 Release Notes

### New Features

#### Bluetooth Enhancements
- **AirTag Spoofing**: Added support for emulating Apple AirTags
- **FlipperZero Spoofing**: Added support for emulating FlipperZero devices
- **Bluetooth Spam**: Enhanced spam functionality with multiple device types
  - Apple devices
  - Google devices
  - Samsung devices
  - Windows devices
  - FlipperZero

#### Command Line Interface
- New command: `sniffbt` - Bluetooth sniffing with AirTag/FlipperZero support
- New command: `blespam` - Enhanced Bluetooth device spam
- New command: `spoofat` - AirTag spoofing interface
- Improved help text and command documentation

#### User Interface
- New menu icons for Bluetooth operations
- Improved status display during Bluetooth operations
- Enhanced error handling and user feedback
- Streamlined menu navigation

#### Utility Functions
- Moved common functions to `utils.h` for better code organization
- Added `macToString` for consistent MAC address formatting
- Added `generateRandomName` for device name generation
- Added `generateRandomMac` for MAC address generation

### Bug Fixes
- Fixed Bluetooth scan/stop functionality
- Improved memory management
- Enhanced error handling for Bluetooth operations
- Fixed menu navigation issues

### How to Use New Features

#### AirTag/FlipperZero Spoofing
1. Navigate to `Bluetooth` > `Attacks` > `AirTag Spoof` or `FlipperZero Spoof`
2. Select `Start Spoofing` to begin
3. Press the **center button** to stop and return to the menu

#### Bluetooth Spam
1. Use the menu: `Bluetooth` > `Attacks` > `BLE Spam`
2. Select target device type
3. Or use command line: `blespam -t <device_type>`

#### Command Line Examples
```
sniffbt -t airtag    # Start AirTag sniffing
blespam -t google    # Spam Google devices
spoofat -t 1        # Spoof AirTag with index 1
```

## Development Plan

### Current Status
- **Fixed**: EAPOL/PMKID scan logging now works correctly with GPS coordinates
- **Fixed**: Resolved double extension issue in file naming (e.g., `.pcap.cap` → `.pcap`)
- **Improved**: Unified log format across all scan modes to match wardrive format
- **Enhanced**: Better error handling for SD card operations

### Task List
- [x] Review and compare file system (SD/SPIFFS/FFat) initialization in Wardrive vs. EAPOL/PMKID Scan modes
- [x] Identify where file system mounting is missing or fails in EAPOL/PMKID Scan
- [x] Implement conditional SD object selection in EAPOL/PMKID scan logging
- [x] Unify EAPOL/PMKID scan log format with executeWarDrive/RunProbeScan
- [x] Fix double extension for .pcap and .log files
- [x] Test EAPOL/PMKID Scan logging after applying fix
- [x] Update all scan modes to use new getTimestampedFilename signature and fix related compilation errors
- [x] Verify Buffer class double extension fix in all scan modes

### Current Goal
Test all scan modes for correct log output and file creation

### Notes
- Wardrive mode successfully creates and writes to the log file (wardrive_[timestamp].log).
- EAPOL/PMKID Scan now correctly creates log files (eapolwardrive_[timestamp].log).
- Unified log format across all scan modes for consistency.
- Fixed file system mounting issues for ESP32-S3 Mini.
- Resolved double extension issues in file naming.

### EAPOL Wardriving Feature

#### Overview
EAPOL Wardriving allows capturing WPA handshakes while moving, with GPS coordinates logged for each capture. This is particularly useful for penetration testing and security assessments of wireless networks.

#### Recent Fixes & Improvements
1. **Fixed File System Mounting**
   - Corrected SD card initialization for ESP32-S3 Mini
   - Added proper error handling for file operations

2. **Unified Log Format**
   - Standardized log format to match wardrive/probe scan formats
   - Added GPS coordinates, timestamps, and signal strength to logs

3. **File Naming**
   - Fixed double extension issue (e.g., `eapol_wardrive_2025-07-05_13-37-04.log`)
   - Added proper timestamp-based naming

4. **Compatibility**
   - Works with both FFAT and standard file systems
   - Supports both SD and SD_MMC interfaces

#### Usage
1. Enable GPS module
2. Insert SD card
3. Start EAPOL scan from the menu
4. Logs will be saved to the SD card with timestamps and GPS data

### EAPOL Wardriving Feature

#### Overview
EAPOL Wardriving allows capturing WPA handshakes while moving, with GPS coordinates logged for each capture. This is particularly useful for penetration testing and security assessments of wireless networks.

#### Recent Fixes & Improvements
1. **Fixed File System Mounting**
   - Corrected SD card initialization for ESP32-S3 Mini
   - Added proper error handling for file operations

2. **Unified Log Format**
   - Standardized log format to match wardrive/probe scan formats
   - Added GPS coordinates, timestamps, and signal strength to logs

3. **File Naming**
   - Fixed double extension issue (e.g., `eapol_wardrive_2025-07-05_13-37-04.log`)
   - Added proper timestamp-based naming

4. **Compatibility**
   - Works with both FFAT and standard file systems
   - Supports both SD and SD_MMC interfaces

#### Usage
1. Enable GPS module
2. Insert SD card
3. Start EAPOL scan from the menu
4. Logs will be saved to the SD card with timestamps and GPS data

### Bluetooth Spoofing Features

#### AirTag & FlipperZero Spoofing

**New in v1.1.0:**
- Added support for AirTag and FlipperZero Bluetooth spoofing
- Menu-based control for starting/stopping spoofing operations
- Center button can now be used to exit spoofing modes and return to the menu

**How to use:**
1. Navigate to `Bluetooth` > `Attacks` > `AirTag Spoof` or `FlipperZero Spoof`
2. Select `Start Spoofing` to begin the spoofing operation
3. Press the **center button** at any time to stop spoofing and return to the menu

**Note:** The spoofing operation can also be stopped via the serial interface using the `stopscan` command.

<br><br>
<p align="center"><img alt="Marauder logo" src="https://github.com/justcallmekoko/ESP32Marauder/blob/master/pictures/marauder3L.jpg?raw=true" width="300"></p>
<p align="center">
  <b>A suite of WiFi/Bluetooth offensive and defensive tools for the ESP32</b>
  <br><br>
  <a href="https://github.com/justcallmekoko/ESP32Marauder/blob/master/LICENSE"><img alt="License" src="https://img.shields.io/github/license/mashape/apistatus.svg"></a>
  <a href="https://gitter.im/justcallmekoko/ESP32Marauder"><img alt="Gitter" src="https://badges.gitter.im/justcallmekoko/ESP32Marauder.png"/></a>
  <a href="https://github.com/justcallmekoko/ESP32Marauder/releases/latest"><img src="https://img.shields.io/github/downloads/justcallmekoko/ESP32Marauder/total" alt="Downloads"/></a>
  <br>
  <a href="https://twitter.com/intent/follow?screen_name=jcmkyoutube"><img src="https://img.shields.io/twitter/follow/jcmkyoutube?style=social&logo=twitter" alt="Twitter"></a>
  <a href="https://www.instagram.com/just.call.me.koko"><img src="https://img.shields.io/badge/Follow%20Me-Instagram-orange" alt="Instagram"/></a>
  <br><br>
  <a href="https://www.tindie.com/products/justcallmekoko/esp32-marauder/"><img src="https://d2ss6ovg47m0r5.cloudfront.net/badges/tindie-larges.png" alt="I sell on Tindie" width="200" height="104"></a>
  <br>
  <a href="https://www.twitch.tv/willstunforfood"><img src="https://assets.stickpng.com/images/580b57fcd9996e24bc43c540.png" alt="Twitch WillStunForFood" width="200"></a>
</p>
    
[![Build and Push](https://github.com/justcallmekoko/ESP32Marauder/actions/workflows/build_push.yml/badge.svg)](https://github.com/justcallmekoko/ESP32Marauder/actions/workflows/build_push.yml)

## Getting Started
Download the [latest release](https://github.com/justcallmekoko/ESP32Marauder/releases/latest) of the firmware.  

Check out the project [wiki](https://github.com/justcallmekoko/ESP32Marauder/wiki) for a full overview of the ESP32 Marauder

# For Sale Now
You can buy the ESP32 Marauder using [this link](https://www.tindie.com/products/justcallmekoko/esp32-marauder/)
