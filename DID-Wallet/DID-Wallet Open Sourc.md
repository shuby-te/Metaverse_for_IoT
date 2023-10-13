# DID-Wallet
did-wallet에 대한 오픈소스 조사

## did-wallet-java
- <https://github.com/ewangplay/did-wallet-java#did-wallet-java>
- 자바 프로그래밍 언어를 기반으로 구현된 wallet
- filesystem wallet과 memory wallet 방식을 모두 지원
- ed25519 키쌍과 같은 Raw Identity Type(기본적인 식별자 유형)을 지원
- 샘플용 main.java에서는 filesystem wallet 방식을 사용하여 지갑을 생성하고, 지갑에 did 및 키쌍을 저장하는 과정을 보여줌

## transmute/did-wallet
- <https://github.com/transmute-industries/did-wallet>
- 자바스크립트 프로그래밍 언어를 기반으로 구현된 wallet
- did-wallet을 생성하고 생성한 wallet을 관리하는 다양한 기능들을 제공
- lock(잠금 및 정보 암호), unlock(잠금 해제), addkey(키 추가), extract(특정 키를 추출), export(지갑 암호화후 반환) 기능들을 지원

## trustfractal/wallet
- <https://github.com/trustfractal/wallet>
- Metamask를 기반으로 구축한 암호화폐 지갑인 Fractal Wallet
- Fractal Wallet 개발환경을 구축하고 분산 ID 자격 증명을 발급 및 저장 가능
- Fractal Wallet은 암호화폐 지갑으로, 암호화폐 자원을 저장하고 관리하는 등 블록체인과 관련된 기술이므로, 
분산 식별 및 신원 관리를 위한 did-wallet과는 주 목적이 다르다.


