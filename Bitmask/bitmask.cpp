#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;


/**
 * A message is divided into multiple 32 bit packets.
 * Each packet is read from MSB to LSB as:
 * 3 bits: message ID
 * 4 bits: total number of packets
 * 3 bits: packet number
 * 2 bits: permission (specified in the 1st packet)
 * 16 bits: file name (spread in multiple packets)
 * 4 bits: not used
 */

/**
 * Task: receive message and create file
 */

int32_t message_id;
int32_t packet_no;
string filename;
int32_t permission;

void process_packet(int32_t packet);
void create_file(const string& fn);
void append_filename_seg(int32_t fn_raw);

int main() {
    vector<int32_t> message_1 = {0x26054520, 0x264554D0, 0x26850000};
    for(const auto& packet : message_1) {
        process_packet(packet);
        cout << "message ID: " << setbase(16) << message_id << ", ";
        cout << "packet No: " << setbase(16) << packet_no << ", ";
        cout << "permission: " << setbase(16) << permission << ", ";
        cout << "filename: "  << filename << endl;
    }
    return 0;
}

void process_packet(int32_t packet) {
    const int32_t mask_message_id = 0xE0000000;
    const int32_t mask_tot_packet = 0x1E000000;
    const int32_t mask_packet_no  = 0x01C00000;
    const int32_t mask_permission = 0x00180000;
    const int32_t mask_filename   = 0x000FFFF0;

    message_id = (packet & mask_message_id) >> 29;
    packet_no = (packet & mask_packet_no) >> 22;
    int32_t tot_packet = (packet & mask_tot_packet) >> 25;
    if(packet_no == 0) {
        permission = (packet & mask_permission) >> 20;
    }
    append_filename_seg((packet & mask_filename) >> 4);
    if(packet_no == tot_packet - 1) {
        create_file(filename);
    }
}

void append_filename_seg(int32_t fn_seg_raw) {
    const int32_t mask_letter1 = 0xFF00;
    const int32_t mask_letter2 = 0x00FF;
    auto letter1 = static_cast<char>((fn_seg_raw & mask_letter1) >> 8);
    auto letter2 = static_cast<char>(fn_seg_raw & mask_letter2);
    filename += letter1;
    filename += letter2;
}

void create_file(const string& fn) {
    cout << "creating file: " << filename + ".txt" << endl;
}
