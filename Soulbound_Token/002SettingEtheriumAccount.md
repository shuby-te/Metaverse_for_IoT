create a SBT Step2 - SettingEtheriumAccount
=============
목표 : 이더리움 계정(지갑세팅)   
------------
### 이더리움 네트워크 종류   
* 메인넷   
  실제화폐가 사용되어 Dapp이 실행되고, 블록체인간의 트랜잭션과 컨트랙트들이 발급되고 이동되는 네트워크
* 테스트넷   
  실제 Dapp을 메인넷에서 실행하기 전에, 테스트하고 개발, 실험하는 네트워크
  테스트넷 종류   
  * speoli   
  * goerli
   
### 이더리움 계정

``` 
이더리움 계정 == 개인 지갑   
```

### 이더리움 계정이 왜 곧 개인 지갑임을 말하는 것일까?   
   
### hardhat.config.js   
```
require("@nomicfoundation/hardhat-toolbox");
require("dotenv").config();

module.exports = {
  solidity: "0.8.4",
  networks: {
    goerli: {
      url: 'https://responsive-quaint-tent.ethereum-goerli.quiknode.pro/4359db6c0520b3e0a419b1c9b936cf9f159b3ac0/',
       accounts: {
        mnemonic : "fat upgrade napkin salad confirm orchard bachelor census nominee olympic wood good",
        path : "m/44'/60'/0/0",
        initiallndes :0,
        count : 20,
        passphrase: "",
      },
    },
  },
};
```
