# ESP32 Marauder
<b>A fork for the ESP32-S3-Mini dev board (16MB flash, 8MB PSRAM on external IC's)</b>

## Current Development Status

### Latest Changes (2025-07-05)
- **Fixed**: EAPOL/PMKID scan logging now works correctly with GPS coordinates
- **Fixed**: Resolved double extension issue in file naming (e.g., `.pcap.cap` → `.pcap`)
- **Improved**: Unified log format across all scan modes to match wardrive format
- **Enhanced**: Better error handling for SD card operations

### Current Focus
- Testing EAPOL/PMKID scan logging across different scenarios
- Ensuring consistent behavior across all scan modes
- Improving file system reliability

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
