#include "hid.h"

#include <raw_hid.h>
#include <string.h>

extern const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS];
extern const uint8_t N_LAYERS;

#define HID_PACKET_SIZE 32

enum raw_hid_commands {
    HID_CMD_UNKNOWN,
    HID_CMD_GET_LAYERS,
    HID_CMD_GET_LAYERS_METADATA,
    HID_EVENT,
};

typedef struct {
    uint8_t report_id;
    uint8_t command_code;
    uint16_t call_id;
    uint8_t packet_number;
    uint8_t total_packets;
} hid_header_t;

typedef struct {
    uint8_t command_code;
    uint16_t call_id;
} hid_command_t;

typedef struct {
    uint8_t n_layers;
    uint8_t rows;
    uint8_t cols;
} hid_layer_metadata_t;

typedef struct {
    uint16_t keycode;
    uint8_t col;
    uint8_t row;
    uint8_t pressed;
    uint8_t mods;
    uint8_t layer;
} hid_event_t;

static uint16_t current_call_id;

static uint16_t next_call_id(void) {
    return ++current_call_id;
}

static void send_hid_data(uint8_t command_code, uint16_t call_id, const uint8_t *data, uint16_t length) {
    const uint8_t header_size = sizeof(hid_header_t);
    const uint8_t payload_size = HID_PACKET_SIZE - header_size;
    const uint8_t total_packets = (length + payload_size - 1) / payload_size;
    uint8_t packet[HID_PACKET_SIZE];
    uint16_t bytes_sent = 0;

    for (uint8_t packet_number = 0; packet_number < total_packets; packet_number++) {
        const uint8_t bytes_remaining = MIN(payload_size, length - bytes_sent);
        const hid_header_t header = {
            .report_id = 0,
            .command_code = command_code,
            .call_id = call_id,
            .packet_number = packet_number,
            .total_packets = total_packets,
        };

        memset(packet, 0, sizeof(packet));
        memcpy(packet, &header, header_size);
        memcpy(packet + header_size, data + bytes_sent, bytes_remaining);
        raw_hid_send(packet, sizeof(packet));
        bytes_sent += bytes_remaining;
    }
}

static void send_layer_data(uint16_t call_id) {
    const uint16_t key_count = N_LAYERS * MATRIX_ROWS * MATRIX_COLS;
    uint16_t layer_data[key_count];
    uint16_t index = 0;

    for (uint8_t layer = 0; layer < N_LAYERS; layer++) {
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                layer_data[index++] = pgm_read_word(&keymaps[layer][row][col]);
            }
        }
    }

    send_hid_data(HID_CMD_GET_LAYERS, call_id, (const uint8_t *)layer_data, sizeof(layer_data));
}

static void send_layer_metadata(uint16_t call_id) {
    const hid_layer_metadata_t metadata = {
        .n_layers = N_LAYERS,
        .rows = MATRIX_ROWS,
        .cols = MATRIX_COLS,
    };
    send_hid_data(HID_CMD_GET_LAYERS_METADATA, call_id, (const uint8_t *)&metadata, sizeof(metadata));
}

void raw_hid_receive(uint8_t *data, uint8_t length) {
    if (length < sizeof(hid_command_t)) {
        return;
    }

    const hid_command_t *command = (const hid_command_t *)data;
    switch (command->command_code) {
        case HID_CMD_GET_LAYERS:
            send_layer_data(command->call_id);
            break;
        case HID_CMD_GET_LAYERS_METADATA:
            send_layer_metadata(command->call_id);
            break;
    }
}

void send_event_to_hid(uint16_t keycode, keyevent_t event) {
    const hid_event_t hid_event = {
        .keycode = keycode,
        .col = event.key.col,
        .row = event.key.row,
        .pressed = event.pressed,
        .mods = get_mods(),
        .layer = get_highest_layer(layer_state | default_layer_state),
    };
    send_hid_data(HID_EVENT, next_call_id(), (const uint8_t *)&hid_event, sizeof(hid_event));
}
