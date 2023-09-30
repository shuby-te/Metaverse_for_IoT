# MQTT Control Messages

## Structure of MQTT Control Packet

An MQTT Control Packet consists of three parts: fixed header, variable header, and payload.


The fixed header in each MQTT Control Packet is shown below. 
![img](./MQTT_fixed_header.png)

## MQTT Control Packet Types

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



