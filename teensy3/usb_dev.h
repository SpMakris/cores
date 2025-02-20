/* Teensyduino Core Library
 * http://www.pjrc.com/teensy/
 * Copyright (c) 2017 PJRC.COM, LLC.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * 1. The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * 2. If the Software is incorporated into a build system that allows
 * selection among a list of target devices, then similar target
 * devices manufactured by PJRC.COM must be included in the list of
 * target devices and selectable in the same manner.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _usb_dev_h_
#define _usb_dev_h_

#define USB_DESC_LIST_DEFINE
#include "usb_desc.h"

#if F_CPU >= 20000000 && !defined(USB_DISABLED)

// This header is NOT meant to be included when compiling
// user sketches in Arduino.  The low-level functions
// provided by usb_dev.c are meant to be called only by
// code which provides higher-level interfaces to the user.

#include "usb_mem.h"

#ifdef __cplusplus
extern "C" {
#endif

void usb_init(void);
void usb_init_serialnumber(void);
void usb_isr(void);
void (*usbMIDI_isr)(void);
void usbMIDI_attach_interrupt(void (*fptr)());
usb_packet_t *usb_rx(uint32_t endpoint);
uint32_t usb_tx_byte_count(uint32_t endpoint);
uint32_t usb_tx_packet_count(uint32_t endpoint);
void usb_tx(uint32_t endpoint, usb_packet_t *packet);
void usb_tx_isochronous(uint32_t endpoint, void *data, uint32_t len);

extern volatile uint8_t usb_configuration;

extern uint16_t usb_rx_byte_count_data[NUM_ENDPOINTS];
static inline uint32_t usb_rx_byte_count(uint32_t endpoint) __attribute__((always_inline));
static inline uint32_t usb_rx_byte_count(uint32_t endpoint)
{
        endpoint--;
        if (endpoint >= NUM_ENDPOINTS) return 0;
        return usb_rx_byte_count_data[endpoint];
}

#ifdef SEREMU_INTERFACE
extern volatile uint8_t usb_seremu_transmit_flush_timer;
extern void usb_seremu_flush_callback(void);
extern volatile uint8_t usb_seremu_online;
#endif

#ifdef KEYBOARD_INTERFACE
extern uint8_t keyboard_modifier_keys;
extern uint8_t keyboard_keys[6];
extern uint8_t keyboard_protocol;
extern uint8_t keyboard_idle_config;
extern uint8_t keyboard_idle_count;
extern volatile uint8_t keyboard_leds;
#endif

#ifdef MIDI_INTERFACE
extern void usb_midi_flush_output(void);
#endif

#ifdef FLIGHTSIM_INTERFACE
extern void usb_flightsim_flush_callback(void);
#endif

#ifdef AUDIO_INTERFACE
extern uint16_t usb_audio_receive_buffer[];
extern uint16_t usb_audio_transmit_buffer[];
extern uint32_t usb_audio_sync_feedback;
extern uint8_t usb_audio_receive_setting;
extern uint8_t usb_audio_transmit_setting;
extern void usb_audio_receive_callback(unsigned int len);
extern unsigned int usb_audio_transmit_callback(void);
extern int usb_audio_get_feature(void *stp, uint8_t *data, uint32_t *datalen);
extern int usb_audio_set_feature(void *stp, uint8_t *buf);
#endif

#ifdef MULTITOUCH_INTERFACE
extern void usb_touchscreen_update_callback(void);
#endif


#ifdef __cplusplus
}
#endif

#ifdef CDC_DATA_INTERFACE
#include "usb_serial.h"
#endif

#ifdef CDC2_DATA_INTERFACE
#include "usb_serial2.h"
#endif

#ifdef CDC3_DATA_INTERFACE
#include "usb_serial3.h"
#endif

#else // F_CPU < 20000000

#ifdef __cplusplus
extern "C" {
#endif

void usb_init(void);

#ifdef __cplusplus
}
#endif


#endif // F_CPU

#endif
