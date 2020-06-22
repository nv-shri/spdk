/*-
 *   BSD LICENSE
 *
 *   Copyright (c) 2020 Mellanox Technologies LTD. All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of Intel Corporation nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef IO_PACER_H
#define IO_PACER_H

#include "spdk/stdinc.h"
#include "spdk/nvmf.h"

struct spdk_io_pacer;
typedef void (*spdk_io_pacer_pop_cb)(void *io);
struct io_pacer_queue_entry {
	uint64_t size;
	STAILQ_ENTRY(io_pacer_queue_entry) link;
};

struct spdk_io_pacer *spdk_io_pacer_create(uint32_t period_ns,
					   uint32_t credit,
					   uint32_t max_credit,
					   uint32_t tuner_period_us,
					   uint32_t tuner_step_ns,
					   spdk_io_pacer_pop_cb pop_cb,
					   void *ctx);
void spdk_io_pacer_destroy(struct spdk_io_pacer *pacer);
int spdk_io_pacer_create_queue(struct spdk_io_pacer *pacer, uint64_t key);
int spdk_io_pacer_destroy_queue(struct spdk_io_pacer *pacer, uint64_t key);
int spdk_io_pacer_push(struct spdk_io_pacer *pacer,
		       uint64_t key,
		       struct io_pacer_queue_entry *entry);
void spdk_io_pacer_get_stat(const struct spdk_io_pacer *pacer,
			    struct spdk_nvmf_transport_poll_group_stat *stat);

#endif /* IO_PACER_H */