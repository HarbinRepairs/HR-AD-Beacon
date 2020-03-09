# HR Ad Beacon

![beacon](HR%20AD%20Beacon%20V1.0/images/beacon.jpg)

## Warnings
THIS INFORMATION IS PROVIDED BY HARBIN REPAIRS AS-IS WITH ABSOLUTELY NO WARRANTY OF ANY KIND, USE AT YOUR OWN RISK. From this point on we do not provide any customer support.

## Documentation
The Arduino code requires the libraries stored in /HR AD Beacon V1.0/Arduino Libraries/ folder (https://github.com/HarbinRepairs/HR-AD-Beacon/tree/master/HR%20AD%20Beacon%20V1.0/Arduino%20Libraries) and you will also need the ESP8266WIFI library (https://arduino-esp8266.readthedocs.io/en/latest/installing.html). The data folder included with the arduino code containing the HTML and logo image will need to be uploaded via SPIFFS. The index.html file is the main page that loads in the captive portal as soon as a user connect to the access point. All of the data is locally stored on the ESP so if you have any hyperlinks they will not load since there is no internet connection when users connects to the access point.

### Images
The logo.jpg file in /data is the image that will be displayed on the left column of the HTML page. It's recommended to use an image no larger than 60KB at a resolution between 320x240 and 640x480, the image must be named logo.jpg, you can use a png but you will need to edit the index.html for it to work. Keep in mind that all this data is stored on a 4MB EEPROM on the ESP8266 and even though it has a couple MB of SPIFFS memory, it isn't very fast.

### Bill of Materials

https://github.com/HarbinRepairs/HR-AD-Beacon/blob/master/HR%20AD%20Beacon%20V1.0/Bill%20of%20Materials.csv

|Qty|Description                        |Part # |Main Links (Affiliate)                                               |eBay Links (Affiliate) |Amazon Links (Affiliate)|
|---|-----------------------------------|-------|---------------------------------------------------------------------|-----------------------|------------------------|
|1  |Wemos D1 Mini                      |N/A    |https://s.click.aliexpress.com/e/_dZEw5Mh                            |https://ebay.to/2Iy7eYR|https://amzn.to/2TSPsEM |
|1  |SSD1306 OLED Module for D1 Mini    |N/A    |https://s.click.aliexpress.com/e/_d7ULdpb                            |https://ebay.to/2TMCAQM|https://amzn.to/39GyPmI |
|   |1/8” Black Acrylic                 |N/A    |https://www.delviesplastics.com/p/Translucent_Cast_Acrylic_Sheet.html|N/A                    |N/A                     |
|2  |Heat Press Nuts M3 x 6mm Length    |N/A    |https://s.click.aliexpress.com/e/_dVW4yU5                            |https://ebay.to/2xmEYWM|https://amzn.to/2TSPDQs |
|   |Lead Free Solder                   |N/A    |I think you know where to find this                                  |N/A                    |N/A                     |
|2  |30mm M3 Screws                     |N/A    |https://s.click.aliexpress.com/e/_dWrpnXB                            |https://ebay.to/2xel7c7|https://amzn.to/38yDvcR |
|1  |USB Wall Adapter or USB Car Charger|T6637ST|https://www.mouser.com/ProductDetail/374-T6637ST                     |N/A                    |N/A                     |
|1  |Micro USB Cable                    |N/A    |I think you know where to find this                                  |https://ebay.to/2TyEFk5|N/A                     |
