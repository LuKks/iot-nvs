#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <esp_err.h>
#include <nvs_flash.h>

#include "../include/nvs.h"

void
nvs_create (const char *space) {
  nvs_handle_t nvs;

  ESP_ERROR_CHECK(nvs_open(space, NVS_READWRITE, &nvs));
  ESP_ERROR_CHECK(nvs_commit(nvs));
  nvs_close(nvs);
}

void
nvs_purge (const char *space) {
  nvs_handle_t nvs;

  ESP_ERROR_CHECK(nvs_open(space, NVS_READWRITE, &nvs));
  ESP_ERROR_CHECK(nvs_erase_all(nvs));
  ESP_ERROR_CHECK(nvs_commit(nvs));
  nvs_close(nvs);
}

void
nvs_write (const char *space, const char *key, const uint8_t *value, size_t length) {
  nvs_handle_t nvs;

  ESP_ERROR_CHECK(nvs_open(space, NVS_READWRITE, &nvs));
  ESP_ERROR_CHECK(nvs_set_blob(nvs, key, value, length));
  ESP_ERROR_CHECK(nvs_commit(nvs));
  nvs_close(nvs);
}

void
nvs_write_string (const char *space, const char *key, const char *value) {
  nvs_handle_t nvs;

  ESP_ERROR_CHECK(nvs_open(space, NVS_READWRITE, &nvs));
  ESP_ERROR_CHECK(nvs_set_str(nvs, key, value));
  ESP_ERROR_CHECK(nvs_commit(nvs));
  nvs_close(nvs);
}

void
nvs_write_bool (const char *space, const char *key, bool value) {
  nvs_handle_t nvs;

  ESP_ERROR_CHECK(nvs_open(space, NVS_READWRITE, &nvs));
  ESP_ERROR_CHECK(nvs_set_u8(nvs, key, value ? 1 : 0));
  ESP_ERROR_CHECK(nvs_commit(nvs));
  nvs_close(nvs);
}

uint8_t *
nvs_read (const char *space, const char *key) {
  nvs_handle_t nvs;

  ESP_ERROR_CHECK(nvs_open(space, NVS_READONLY, &nvs));

  size_t size;
  esp_err_t err = nvs_get_blob(nvs, key, NULL, &size);

  if (err == ESP_ERR_NVS_NOT_FOUND) {
    nvs_close(nvs);

    return NULL;
  } else {
    ESP_ERROR_CHECK(err);
  }

  uint8_t *value = malloc(size);
  ESP_ERROR_CHECK(nvs_get_blob(nvs, key, value, &size));

  nvs_close(nvs);

  return value;
}

char *
nvs_read_string (const char *space, const char *key) {
  nvs_handle_t nvs;

  ESP_ERROR_CHECK(nvs_open(space, NVS_READONLY, &nvs));

  size_t size;
  esp_err_t err = nvs_get_str(nvs, key, NULL, &size);

  if (err == ESP_ERR_NVS_NOT_FOUND) {
    nvs_close(nvs);

    return NULL;
  } else {
    ESP_ERROR_CHECK(err);
  }

  char *value = malloc(size);
  ESP_ERROR_CHECK(nvs_get_str(nvs, key, value, &size));

  nvs_close(nvs);

  return value;
}

bool
nvs_read_bool (const char *space, const char *key) {
  nvs_handle_t nvs;

  ESP_ERROR_CHECK(nvs_open(space, NVS_READONLY, &nvs));

  uint8_t value;
  esp_err_t err = nvs_get_u8(nvs, key, &value);

  if (err == ESP_ERR_NVS_NOT_FOUND) {
    nvs_close(nvs);

    return false;
  } else {
    ESP_ERROR_CHECK(err);
  }

  nvs_close(nvs);

  return value ? true : false;
}

void
nvs_delete (const char *space, const char *key) {
  nvs_handle_t nvs;

  ESP_ERROR_CHECK(nvs_open(space, NVS_READWRITE, &nvs));

  esp_err_t err = nvs_erase_key(nvs, key);

  if (err != ESP_ERR_NVS_NOT_FOUND) {
    ESP_ERROR_CHECK(err);
  }

  ESP_ERROR_CHECK(nvs_commit(nvs));
  nvs_close(nvs);
}
