#pragma once

#ifndef Buffer_h
#define Buffer_h
#ifdef HAS_SCREEN
  #include "Display.h"
#endif
#include "Arduino.h"
#include "FS.h"
#include "settings.h"
#include "esp_wifi_types.h"

#define BUF_BLOCKS 24  // Had to reduce buffer size to save RAM. GG @spacehuhn @schrab 3 -> 6
  #if defined BOARD_HAS_PSRAM
    #define EWH_MALLOC ps_malloc
  #else
    #define EWH_MALLOC malloc
  #endif

#define BUF_SIZE BUF_BLOCKS * 1024 
#define SNAP_LEN 2324 // max len of each recieved packet

//extern bool useSD;

extern Settings settings_obj;
#ifdef HAS_SCREEN
  extern Display display_obj;
#endif
class Buffer {
  public:
    Buffer();
    void pcapOpen(String file_name, fs::FS* fs, bool serial);
    void logOpen(String file_name, fs::FS* fs, bool serial);
    void append(wifi_promiscuous_pkt_t *packet, int len);
    void append(String log);
    void save();
  private:
    void createFile(String name, bool is_pcap);
    void open(bool is_pcap);
    void openFile(String file_name, fs::FS* fs, bool serial, bool is_pcap);
    void add(const uint8_t* buf, uint32_t len, bool is_pcap);
    void write(int32_t n);
    void write(uint32_t n);
    void write(uint16_t n);
    void write(const uint8_t* buf, uint32_t len);
    void saveFs();
    void saveSerial();
    
    uint8_t* bufA;
    uint8_t* bufB;

    uint32_t bufSizeA = 0;
    uint32_t bufSizeB = 0;

    bool writing = false; // acceppting writes to buffer
    bool useA = true; // writing to bufA or bufB
    bool saving = false; // currently saving onto the SD card

    #ifdef USE_FFAT
    String fileName = "/0.cap";
    #else
    String fileName = "/0.pcap";
    #endif
    File file;
    fs::FS* fs;
    bool serial;
};

#endif
