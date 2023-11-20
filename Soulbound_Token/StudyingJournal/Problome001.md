Problome001 : 설치 작업 중 문제 발생   
=============
* 문제 :
  노드를 설치하고, hardhat를 설치한 후 추가로 @nomicfoundation/hardhat-toolbox @openzeppelin/contracts@4.0.0를 설치하려는 데 오류가 발생하여 설치 못하는 문제가 발생했다

### 오류 코드 :
    npm ERR! code ERESOLVE ERESOLVE unable to resolve dependency tree   

### 오류 원인 :   
* 근원적으로 dependency들의 호환성이 맞지 않아 문제가 발생하였다. 그러면 호환성 맞지 않은 문제가 생긴 이유는 무엇이냐
    * 바로 2021년 2월 출시된 npm 7버전부터 추가된 peerDependencies를 자동으로 설치하는 기능 때문이다.   
1. 먼저 npm으로 hardhat를 설치해 주었는데 이때 peerDependencies가 자동으로 설치된다.
2. 이후 또 npm으로 hardhat의 확장 패킷인 nomicfoundation/hardhat-toolbox 설치하는데 동일한 의존성을 가지지만 버전이 다른 peerDependencies를 설치하게 충돌이 일어나 에러가 발생한다.      
   
### 오류 해결 :   
    설치 명령어 뒤에 옵션으로 --force 혹은 --legacy-peer-deps 를 붙여주면 된다.   
* 이유   
 --force : 충돌이 일어나도 강제로 설치   
 --legacy-peer-deps : 설치할 때 자동으로 peerDependencies을 설치하지 않게 한다 
