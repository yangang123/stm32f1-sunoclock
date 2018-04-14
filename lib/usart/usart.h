/*
2018 David DiPaola
licensed under CC0 (public domain, see https://creativecommons.org/publicdomain/zero/1.0/)
*/

#ifndef _USART_H
#define _USART_H

void
usart_init(struct usart * urt, size clkspd, size baud);

void
usart_write_chr(struct usart * urt, u8 value);

void
usart_write_hex_u4(struct usart * urt, u8 hex);

void
usart_write_hex_u8(struct usart * urt, u8 hex);

void
usart_write_hex_u16(struct usart * urt, u16 hex);

void
usart_write_hex_u32(struct usart * urt, u32 hex);

void
usart_write_str(struct usart * urt, const u8 * value);

void
usart_write_str_nl(struct usart * urt, const u8 * value);

#endif

