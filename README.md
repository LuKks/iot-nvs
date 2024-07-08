# nvs

Non-Volatile Storage functions in C for IoT

## Usage

```c
#include <nvs_flash.h>
#include <esp_err.h>

#include "nvs.h"

void app_main () {
  ESP_ERROR_CHECK(nvs_flash_init());

  nvs_create("wifi");

  nvs_write_string("wifi", "connect-ssid", "Home AP");
  nvs_write_string("wifi", "connect-pass", "1234");

  char *ssid = nvs_read_string("wifi", "connect-ssid");
  char *pass = nvs_read_string("wifi", "connect-pass");

  // ...

  free(ssid);
  free(pass);

  ESP_ERROR_CHECK(nvs_flash_deinit());
}
```

## API

See [`include/nvs.h`](include/nvs.h) for the public API.

## License

MIT
