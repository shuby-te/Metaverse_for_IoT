# MQTT Control Messages

## Structure of MQTT Control Packet

An MQTT Control Packet consists of three parts: fixed header, variable header, and payload.


| **Fixed Header, presented in all MQTT Control Packets**|
|:--------------:|
| **Variable Header, presented in some MQTT Control Packets** |
| **Payload, presented in Some MQTT Control Packets** |

The fixed header in each MQTT Control Packet is shown below. 

The size of the fixed header is 2 bytes. The first byte represents the packet type and specific flag for that control type. The second byte represents the remaining length.

![img](./MQTT_fixed_header.png)


## MQTT Control Packet Type
MQTT Control Packet type is positioned at bits 7 - 4 in the first byte.

| Name | Value | Direction of flow | Description |
|:------:|:-----:|:-----------:|:------:|
| Reserved | 0 | Forbidden | Reserved |
| CONNECT | 1 | Client -> Server | Connection request |
| CONNACK | 2 | Server -> Client | Connect acknowledgement |
| PUBLISH | 3 | Client -> Server or Server -> Client | Publish message |
| PUBACK | 4 | Client -> Server or Server -> Client | Publlish achnowledgement (QoS 1) |
| PUBREC | 5 | Client -> Server or Server -> Client | PUblish received (QoS 2 delivery part 1) |
| PUBREL | 6 | Client -> Server or Server -> Client | Publish release (QoS 2 delivery part 2) |
| PUBCOMP | 7 | Client -> Server or Server -> Client | Publish complete (QoS 2 delivery part 3) |
| SUBSCRIBE | 8 | Client -> Server | Subscribe request |
| SUBACK | 9 | Server -> Client | Subscribe acknowledgement |
| UNSUBCRIBE | 10 | Client -> Server | Unsubcribe request |
| UNSUBACK | 11 | Server -> Client | Unsubscribe acknowledgement |
| PINGREQ | 12 | Client -> Server | PING request |
| PINGRESP | 13 | Server -> Client | PING acknowledgement |
| DISCONNECT | 14 | Client -> Server or Server -> Client | Disconnect notification |
| AUTH | 15 | Client -> Server or Server -> Client | Authentication exchange |

## MQTT Flags

The remaining bits[3-0] of the first byte in the Fixed Header contain flags specific to each MQTT Control packet type.

| MQTT Control Packets | Fixed Header Flags | Bit 3 | Bit 2| Bit 1 | Bit 0 |
|:------:|:-----:|:------:|:------:| :------:|:------:|
| CONNECT | Reserved | 0 | 0 | 0 | 0 |
| CONNACK | Reserved | 0 | 0 | 0 | 0 |
| PUBLISH | Reserved | DUP | QoS | QoS | RETAIN |
| PUBACK | Reserved | 0 | 0 | 0 | 0 |
| PUBREC | Reserved | 0 | 0 | 0 | 0 |
| PUBREL | Reserved | 0 | 0 | 1 | 0 |
| PUBCOMP | Reserved | 0 | 0 | 0 | 0 |
| SUBSCRIBE | Reserved | 0 | 0 | 1 | 0 |
| SUBACK | Reserved | 0 | 0 | 0 | 0 |
| UNSUBCRIBE | Reserved | 0 | 0 | 1 | 0 |
| UNSUBACK | Reserved | 0 | 0 | 0 | 0 |
| PINGREQ | Reserved | 0 | 0 | 0 | 0 |
| PINGRESP | Reserved | 0 | 0 | 0 | 0 |
| DISCONNECT | Reserved |0 | 0 | 0 | 0 |
| AUTH | Reserved | 0 | 0 | 0 | 0 |

## Remaining length

* The Remaining Length is a Variable Byte Integer representing the number of bytes remaining within the current Control Packet, including data in the Variable Header and the Payload. 
* The Remaining Length does not include the bytes used to encode the Remaining Length. 
* The packet size is the total number of bytes in an MQTT Control Packet. 
* This is equal to the length of the Fixed Header plus the Remaining Length.
