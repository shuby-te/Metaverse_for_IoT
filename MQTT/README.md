# MQTT(Message Queuing Telemetry Transport)

MQTT is designed as an extremely lightweight publish/subscribe messaging transport ideal for connecting remote devices with a small code footprint and minimal network bandwidth.

## Features of MQTT
* Lightweight and Efficient
  - MQTT message headers are small to optimize network bandwidth.
* Bi-directional Communication
  - MQTT allows for messaging between the device to the cloud and the cloud to the device. It makes for easy broadcasting messages to a group of things.
* Scale to Millions of Things
  - MQTT can scale to connect with millions of IoT devices
* Reliable Message Delivery
  - MQTT defines 3 QoS(Quality of Service) levels: 0 - at most once, 1 - at least once, and 2 - exactly once.
* Support for Unreliable Networks
  - MQTT's support for persistent sessions reduces the time to reconnect the client with the broker.
* Security Enabled
  - MQTT encrypts messages easily using TLS and authenticates clients using modern authentication protocols, such as OAuth.

## MQTT Publish/Subscribe Architecture
![img](https://mqtt.org/assets/img/mqtt-publish-subscribe.png) 
(source: https://mqtt.org)

## Info related to MQTT
* [MQTT Messages]
* [Open Sources]

## Questions to be answered by myself
* How does the MQTT client obtain what kinds of topics that producers provide?
* How does the MQTT client obtain the publisher's information?
* Is there a mechanism to aggregate encryption for dedicated group?

## References 
* Designated-Verifier Aggregate Signature Scheme With Sensitive Data Privacy Protection for Permissioned Blockchain-Assisted IIoT

   
