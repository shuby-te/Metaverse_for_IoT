Create a SBT Step 1 - setting Project   
=============   
목표 : 프로젝트 설치 
-------------
   
### 솔바운드 토큰을 받기 위해 필요한 것   
1. 블록체인 플랫폼 계정과 해당 플랫폼의 네트워크 
2. 개인 디지털 지갑과 개인 키

### 솔바운트 토큰을 만들기 위해 코드 작성 시 필요한 것   
1. node
2. hardHat
3. @openzeppelin/contracts
4. @nomicfoundation/hardhat-toolbox
5. dotenv
6. devDependencies: hardhat
7. python
8. JavaScript

## 프로젝트 준비   
### 1. node를 설치한다   
 
* node란?   
JavaScript로 작성된 프로그램을 브라우저 없이 운영체제에서 바로 실행시켜주는 런타임이자 런타임 환경이다.
    
   * 런타임이란?   
     해당 프로그램이 필요한 자원(Ram, 시스템 변수, 환경 변수 등)을 할당받고, 이것을 사용해서 어떤 처리를 하고 있는 상태

   * 런타임 환경이란?   
     애플리케이션이 OS의 시스템자원에 접근할 수 있도록 해주는 실행 환경

   
### 2. 명령 프롬프트 창에서 Soulbound-token 폴더를 생성하고, Soulbound-token 폴더로 위치를 옮긴다   
    mkdir soulbound-tokens && cd soulbound-tokens   

### 3. npm 프로젝트를 초기화 시킨다.   
    npm init -y   

* -y 의미   
node.js 프로젝트 초기화시 사용되는 옵션으로 해당 옵션을 통해 프로젝트의 기본양식을 자동으로 설정해준다.

        
### 4. 해당 폴더 위치에 hardHat를 설치한다   
    npm install --save-dev hardhat   
   
* npm이란?   
node.js 환경에서 사용되는 자바스크립트용 패키지 매니저이다. package.json 파일을 통해 프로젝트 정보와 패키지의 의존성을 관리한다.

   * 의존성이란?   
     어떠한 코드 파일이나 프로젝트가 다른 코드파일이나 프로젝트와 관계를 가지고 있는 것
  
* --save-dev란?    
package.json 파일에 있는 devDependencies 항목에 해당 패키지 정보가 추가된다.    

    * devDependencies란?   
      개발 및 테스트에서 필요한 패키지를 포함하는 곳을 의미한다. 추가로 Dependencies는 프로그램이 실제로 배포됐을 때 실행되는 환경에 필요한 패키지를 포함하는 곳이다.
   
* hardHat이란?   
hardhat은 ethereum 개발을 할 때 compile, deploy, test를 모두 진행할 수 있는 개발 프레임워크이다.

#### 프레임워크 VS 라이브러리   
* 라이브러리란?   
라이브러리는 개발에 필요한 재사용이 가능한 기능들을 미리 구현해놓은 도구들의 집합. 코드 흐름의 제어권은 오직 개발자한테 주어진다
    
* 프레임워크란?   
라이브러리를 포함해 개발에 필요한 도구들을 사용하기 위한 뼈대 즉, 설계와 구현의 재사용이 가능하게끔(도구) 상호 협력하는 클래스와 인터페이스의 집합. 코드 흐름의 제어권이 프레임워크에게 주어진다.

### 5. @openzeppelin/contracts와 @nomicfoundation/hardhat-toolbox를 설치한다.
    npm install dotenv @nomicfoundation/hardhat-toolbox @openzeppelin/contracts@4.0.0

* dotenv란?   
환경변수를 설정하고 읽을 수 있는 라이브러리로 주로 민감한 정보를 환경변수로 관리하는데 사용된다.
    * 환경변수란?
      환경변수는 프로세스가 컴퓨터에서 동작하는 방식에 영향을 미치는, 동적인 값들의 모임을 말한다. 환경변수는 프로세스가 어떠한 작업을 할 때 필요로 하는 정보를 손쉽게 접근하고 처리할 수 있도록 해준다. 

* openzeppelin이란?
  smart contract를 개발할 때 사용하는 라이브러리이다.   
> 현재 추정 - openzeppelin의 라이브러리에 있는 스마트 컨트랙트 관련 패키지를 다운 받는 것으로 추정

* nomicfoundation이란?
> 현재 추정 - hardHat을 배포한 회사가 nomicfoundation인데, 이 회사명의 패키지에서 hardhat-toolbox 패키지를 설치하는 것으로 추정   
> * 궁금한 점 - 그러면 hardhat이라는 패키지를 먼저 설치하는 게 필요한가? hardhat과 해당 다운로드 명령어의 관계 분석 요망

### 6. hardHat을 초기화 시킨다.   
    npx hardhat init   

* npx란?
  node.js에서 사용되는 패키지 매니저이다. 실행하고자 하는 패키지 경로를 찾고 실행시켜준다. 해당 코드는 hartdhat 패키지를 찾아서 초기화시키는 작업을 요청한 것이다.   
