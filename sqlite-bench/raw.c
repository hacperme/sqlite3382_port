// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#include "bench.h"

static void raw_calloc(Raw *raw_) {
  raw_->data_size_ = kNumData;
  raw_->data_ = pvPortCalloc(sizeof(double), raw_->data_size_);
  raw_->pos_ = 0;
}

static void raw_realloc(Raw *raw_) {
  raw_->data_size_ *= 2;
  raw_->data_ = pvPortRealloc(raw_->data_, sizeof(double) * raw_->data_size_);
  if (!raw_->data_) {
    SQLITE_BENCHMARK_LOG(stderr, "pvPortRealloc failed\n");
    #ifndef SQLITE_OS_QUEC_RTOS
    exit(1);
    #endif
  }
}

void raw_clear(Raw *raw_) {
  if (raw_->data_)
    vPortFree(raw_->data_);
  raw_calloc(raw_);
}

void raw_free(Raw *raw_) {
  if (raw_->data_)
    vPortFree(raw_->data_);
  raw_->data_size_ = 0;
  raw_->pos_ = 0;
}

void raw_add(Raw *raw_, double value) {
  if (!raw_->data_)
    raw_calloc(raw_);
  if (raw_->data_size_ < raw_->pos_ + 1)
    raw_realloc(raw_);
  raw_->data_[raw_->pos_] = value;
  raw_->pos_++;
}

char* raw_to_string(Raw *raw_) {
  if (!raw_->data_)
    raw_calloc(raw_);
  size_t r_size = 1024;
  char *r = pvPortMalloc(sizeof(char) * r_size);
  strcpy(r, "");
  char buf[200];
  for (int i = 0; i < raw_->pos_; i++) {
    snprintf(buf, sizeof(buf), "%.4f\n", raw_->data_[i]);
    if (r_size < strlen(r) + strlen(buf)) {
      r = pvPortRealloc(r, r_size * 2);
      r_size *= 2;
    }
    strcat(r, buf);
  }
  return r;
}

void raw_print(FILE *stream, Raw *raw_) {
  if (!raw_->data_)
    raw_calloc(raw_);
  SQLITE_BENCHMARK_LOG(stream, "num,time\n");
  for (int i = 0; i < raw_->pos_; i++)
    SQLITE_BENCHMARK_LOG(stream, "%d,%.4f\n", i, raw_->data_[i]);
}
