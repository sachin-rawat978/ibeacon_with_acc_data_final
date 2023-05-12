#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main()
{
    float prev_x = 0.0f;
    float prev_y = 0.0f;
    float prev_z = 0.0f;
    int first_data = 1;
    for (;;)
    {
        uint8_t raw_data[50]; // Assuming a maximum length of 50 bytes for the raw data
        char hex_string[101]; // Assuming a maximum length of 100 characters for the hex string

        // Prompt the user to enter the hex string
        printf("\nEnter the raw data as a hex string (without 0x prefix): ");
        scanf("%100s", hex_string);

        // Convert the hex string to raw data
        int len = 0;
        for (int i = 0; hex_string[i] != '\0'; i += 2)
        {
            sscanf(&hex_string[i], "%2hhX", &raw_data[len]);
            len++;
        }

        // Process the raw data
        if (raw_data[7] == 0x12 && raw_data[11] == 0xA1 && raw_data[10] == 0xFF && raw_data[9] == 0xE1)
        {
            /** @brief Give the Battery level
             *  Full = 100%     *
             */
            int battery_level = raw_data[13];
            printf("\tBattery level: %d\t", battery_level);

            /* Print MAC address */
            char mac_addr[18];
            sprintf(mac_addr, "%02X:%02X:%02X:%02X:%02X:%02X", raw_data[20], raw_data[21], raw_data[22], raw_data[23], raw_data[24], raw_data[25]);
            printf("||  MAC address: %s\n", mac_addr);

            // Accelerometer data packet
            float x = ((float)((int16_t)((raw_data[14]) | raw_data[15]))) / 256.0f;
            float y = ((float)((int16_t)((raw_data[16]) | raw_data[17]))) / 256.0f;
            float z = ((float)((int16_t)((raw_data[18]) | raw_data[19]))) / 256.0f;

            /* Convert to g-units */
            x = (x / 64.0f) - 1.0f;
            y = (y / 64.0f) + 0.5f;
            z = (z / 64.0f) - 1.23f;

            printf("\tAccelerometer values are X: %f ||Y: %f ||Z: %f\n", x, y, z);
            // Check if the tag is moving
            if (fabs(x - prev_x) > 0.005f || fabs(y - prev_y) > 0.005f || fabs(z - prev_z) > 0.005f)
            {
                if (first_data)
                {
                    first_data = 0;
                }
                else
                {
                    printf("\tTag is moving\n");
                }
            }
            else
            {
                printf("\tTag is stationary\n");
            }

            // Store current values as previous values for next iteration
            prev_x = x;
            prev_y = y;
            prev_z = z;
        }
        else if (raw_data[3] == 0x1A && raw_data[7] == 0x02 && raw_data[8] == 0x15)
        {
            // iBeacon data packet
            uint8_t uuid[16];
            for (int i = 0; i < 16; i++)
            {
                uuid[i] = raw_data[9 + i];
            }

            int8_t rssi = (int8_t)raw_data[29];

            printf("\tiBeacon UUID: ");
            for (int i = 0; i < 16; i++)
            {
                printf("%02X", uuid[i]);
            }
            printf("\n");
            printf("\tiBeacon RSSI: %d\n", rssi);
        }
    }
}
