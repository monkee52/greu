
/*
 * Copyright (c) 2008 David Gwynne <loki@animata.net>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef _LOG_H_
#define _LOG_H_

struct __logger {
#ifdef __linux__
	void (*err)(int, const char *, ...)
	    __attribute__((__format__ (printf, 2, 3)));
	void (*errx)(int, const char *, ...)
	    __attribute__((__format__ (printf, 2, 3)));
#elif _WIN32
	void (*err)(int, const char *, ...)
		_Printf_format_string_;
	void (*errx)(int, const char *, ...)
		_Printf_format_string_;
#else
	__dead void (*err)(int, const char *, ...)
	    __attribute__((__format__ (printf, 2, 3)));
	__dead void (*errx)(int, const char *, ...)
	    __attribute__((__format__ (printf, 2, 3)));
#endif
#ifdef _WIN32
	void (*warn)(const char *, ...)
		_Printf_format_string_;
	void (*warnx)(const char *, ...)
		_Printf_format_string_;
	void (*info)(const char *, ...)
		_Printf_format_string_;
	void (*debug)(const char *, ...)
		_Printf_format_string_;
#else
	void (*warn)(const char *, ...)
	    __attribute__((__format__ (printf, 1, 2)));
	void (*warnx)(const char *, ...)
	    __attribute__((__format__ (printf, 1, 2)));
	void (*info)(const char *, ...)
	    __attribute__((__format__ (printf, 1, 2)));
	void (*debug)(const char *, ...)
	    __attribute__((__format__ (printf, 1, 2)));
#endif
};

extern const struct __logger *__logger;

#ifndef _WIN32
#define lerr(_e, _f...) __logger->err((_e), _f)
#define lerrx(_e, _f...) __logger->errx((_e), _f)
#define lwarn(_f...) __logger->warn(_f)
#define lwarnx(_f...) __logger->warnx(_f)
#define linfo(_f...) __logger->info(_f)
#define ldebug(_f...) __logger->debug(_f)
#else
#define lerr(_e, ...) __logger->err((_e), __VA_ARGS__)
#define lerrx(_e, ...) __logger->errx((_e), __VA_ARGS__)
#define lwarn(...) __logger->warn(__VA_ARGS__)
#define lwarnx(...) __logger->warnx(__VA_ARGS__)
#define linfo(...) __logger->info(__VA_ARGS__)
#define ldebug(...) __logger->debug(__VA_ARGS__)
#endif

void	logger_syslog(const char *);

#endif /* _LOG_H_ */
