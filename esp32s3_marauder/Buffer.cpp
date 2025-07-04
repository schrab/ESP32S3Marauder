#include "Buffer.h"
#include "lang_var.h"

Buffer::Buffer(){
  bufA = (uint8_t*)malloc(BUF_SIZE);
  log_e("Success. malloc %d bytes for buffer 1", BUF_SIZE );
  if( bufA == NULL ) {
    log_e("Panic! Can't malloc %d bytes for buffer 1", BUF_SIZE );
    
  }
  bufB = (uint8_t*)malloc(BUF_SIZE);
  log_e("Success. malloc %d bytes for buffer 2", BUF_SIZE );
  if( bufB == NULL ) {
    log_e("Panic! Can't malloc %d bytes for buffer 2", BUF_SIZE );
    
  }
  
}

void Buffer::createFile(String name, bool is_pcap){
  // Check if the name already has an extension
  bool has_extension = (name.endsWith(".pcap") || name.endsWith(".cap") || name.endsWith(".log"));
  
  if (has_extension) {
    // If name already has an extension, use it as is
    fileName = "/" + name;
  } else {
    // Otherwise, add the appropriate extension
    if (is_pcap) {
      #ifdef USE_FFAT
      fileName = "/" + name + ".cap";
      #else
      fileName = "/" + name + ".pcap";
      #endif
    } else {
      fileName = "/" + name + ".log";
    }
  }

  // If file exists, add number suffix before the extension
  if(fs->exists(fileName)) {
    int i = 1;
    String base_name = name;
    String ext = "";
    
    // Extract extension if it exists
    int last_dot = name.lastIndexOf('.');
    if (last_dot != -1) {
      base_name = name.substring(0, last_dot);
      ext = name.substring(last_dot);
    } else {
      // No extension in original name, use default
      ext = is_pcap ? 
        #ifdef USE_FFAT
        ".cap" : ".log";
        #else
        ".pcap" : ".log";
        #endif
    }
    
    do {
      fileName = "/" + base_name + "_" + String(i) + ext;
      i++;
    } while(fs->exists(fileName));
  }

  Serial.println(fileName);
  
  file = fs->open(fileName, FILE_WRITE);
  if(!file) {
    Serial.println("failed to create file " + fileName);
    return;
  }
  file.close();
}

void Buffer::open(bool is_pcap){
  bufSizeA = 0;
  bufSizeB = 0;

  bufSizeB = 0;

  writing = true;

  if (is_pcap) {
    write(uint32_t(0xa1b2c3d4)); // magic number
    write(uint16_t(2)); // major version number
    write(uint16_t(4)); // minor version number
    write(int32_t(7)); // GMT to local correction
    write(uint32_t(0)); // accuracy of timestamps
    write(uint32_t(SNAP_LEN)); // max length of captured packets, in octets
    write(uint32_t(105)); // data link type
  }
}

void Buffer::openFile(String file_name, fs::FS* fs, bool serial, bool is_pcap) {
  bool save_pcap = settings_obj.loadSetting<bool>("SavePCAP");
  if (!save_pcap) {
    Serial.println("Save pcap disabled");
    this->fs = NULL;
    this->serial = false;
    writing = false;
    return;
  }
  this->fs = fs;
  this->serial = serial;
  if (this->fs) {
    Serial.print("Creating file ");
    Serial.println(file_name);
    createFile(file_name, is_pcap);
  }
  if (this->fs || this->serial) {
    open(is_pcap);
    Serial.println("File open");
  } else {
    Serial.println("Writing disabled");
    writing = false;
  }
}

void Buffer::pcapOpen(String file_name, fs::FS* fs, bool serial) {
  openFile(file_name, fs, serial, true);
}

void Buffer::logOpen(String file_name, fs::FS* fs, bool serial) {
  openFile(file_name, fs, serial, false);
}

void Buffer::add(const uint8_t* buf, uint32_t len, bool is_pcap){
  // buffer is full -> drop packet
  if((useA && bufSizeA + len >= BUF_SIZE && bufSizeB > 0) || (!useA && bufSizeB + len >= BUF_SIZE && bufSizeA > 0)){
    //Serial.print(";"); 
    return;
  }
  
  if(useA && bufSizeA + len + 16 >= BUF_SIZE && bufSizeB == 0){
    useA = false;
    //Serial.println("\nswitched to buffer B");
  }
  else if(!useA && bufSizeB + len + 16 >= BUF_SIZE && bufSizeA == 0){
    useA = true;
    //Serial.println("\nswitched to buffer A");
  }

  uint32_t microSeconds = micros(); // e.g. 45200400 => 45s 200ms 400us
  uint32_t seconds = (microSeconds/1000)/1000; // e.g. 45200400/1000/1000 = 45200 / 1000 = 45s

  microSeconds -= seconds*1000*1000; // e.g. 45200400 - 45*1000*1000 = 45200400 - 45000000 = 400us (because we only need the offset)
  
  if (is_pcap) {
    write(seconds); // ts_sec
    write(microSeconds); // ts_usec
    write(len); // incl_len
    write(len); // orig_len
  }
  
  write(buf, len); // packet payload
}

void Buffer::append(wifi_promiscuous_pkt_t *packet, int len) {
  bool save_packet = settings_obj.loadSetting<bool>(text_table4[7]);  // SavePCAP
  if (save_packet) {
    add(packet->payload, len, true);
  }
}

void Buffer::append(String log) {
  bool save_packet = settings_obj.loadSetting<bool>(text_table4[7]);  // SavePCAP
  if (save_packet) {
    add((const uint8_t*)log.c_str(), log.length(), false);
  }
}

void Buffer::write(int32_t n){
  uint8_t buf[4];
  buf[0] = n;
  buf[1] = n >> 8;
  buf[2] = n >> 16;
  buf[3] = n >> 24;
  write(buf,4);
}

void Buffer::write(uint32_t n){
  uint8_t buf[4];
  buf[0] = n;
  buf[1] = n >> 8;
  buf[2] = n >> 16;
  buf[3] = n >> 24;
  write(buf,4);
}

void Buffer::write(uint16_t n){
  uint8_t buf[2];
  buf[0] = n;
  buf[1] = n >> 8;
  write(buf,2);
}

void Buffer::write(const uint8_t* buf, uint32_t len){
  if(!writing) return;
  while(saving) delay(10);
  
  if(useA){
    memcpy(&bufA[bufSizeA], buf, len);
    bufSizeA += len;
  }else{
    memcpy(&bufB[bufSizeB], buf, len);
    bufSizeB += len;
  }
}

void Buffer::saveFs(){
  file = fs->open(fileName, FILE_APPEND);
  if (!file) {
    Serial.println(text02+fileName+"'");
    return;
  }
  #ifdef HAS_SCREEN
  display_obj.tft.setTextSize(1);
  display_obj.tft.setFreeFont(NULL);
  display_obj.tft.setCursor(0, 0);
  display_obj.tft.setTextWrap(false);
  display_obj.tft.setTextColor(TFT_WHITE, TFT_RED);
  display_obj.tft.drawString("SD", SCREEN_WIDTH - 12, 1, 1);
  #endif
  if(useA){
    if(bufSizeB > 0){
      file.write(bufB, bufSizeB);
    }
    if(bufSizeA > 0){
      file.write(bufA, bufSizeA);
    }
  } else {
    if(bufSizeA > 0){
      file.write(bufA, bufSizeA);
    }
    if(bufSizeB > 0){
      file.write(bufB, bufSizeB);
    }
  }

  file.close();
  #ifdef HAS_SCREEN
  display_obj.tft.fillRect(SCREEN_WIDTH -12, 0, 12, STATUS_BAR_WIDTH, STATUSBAR_COLOR);
  display_obj.tft.setTextColor(TFT_YELLOW, STATUSBAR_COLOR);
  display_obj.tft.drawString("SD", SCREEN_WIDTH - 12, 1, 1);
  #endif
}

void Buffer::saveSerial() {
  // Saves to main console UART, user-facing app will ignore these markers
  // Uses / and ] in markers as they are illegal characters for SSIDs
  const char* mark_begin = "[BUF/BEGIN]";
  const size_t mark_begin_len = strlen(mark_begin);
  const char* mark_close = "[BUF/CLOSE]";
  const size_t mark_close_len = strlen(mark_close);

  // Additional buffer and memcpy's so that a single Serial.write() is called
  // This is necessary so that other console output isn't mixed into buffer stream
  uint8_t* buf = (uint8_t*)malloc(mark_begin_len + bufSizeA + bufSizeB + mark_close_len);
  uint8_t* it = buf;
  memcpy(it, mark_begin, mark_begin_len);
  it += mark_begin_len;

  if(useA){
    if(bufSizeB > 0){
      memcpy(it, bufB, bufSizeB);
      it += bufSizeB;
    }
    if(bufSizeA > 0){
      memcpy(it, bufA, bufSizeA);
      it += bufSizeA;
    }
  } else {
    if(bufSizeA > 0){
      memcpy(it, bufA, bufSizeA);
      it += bufSizeA;
    }
    if(bufSizeB > 0){
      memcpy(it, bufB, bufSizeB);
      it += bufSizeB;
    }
  }

  memcpy(it, mark_close, mark_close_len);
  it += mark_close_len;
  Serial.write(buf, it - buf);
  free(buf);
}

void Buffer::save() {
  saving = true;
  // SD Writing
    

  if((bufSizeA + bufSizeB) == 0){
    saving = false;
    return;
  }

  if(this->fs) saveFs();
  if(this->serial) saveSerial();

  bufSizeA = 0;
  bufSizeB = 0;

  saving = false;
  // SD idle
  
  
}
