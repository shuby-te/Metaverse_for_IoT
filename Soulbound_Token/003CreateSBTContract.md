Create a SBT Step3 - CreateSBTContract
=============
목표 : Solity언어로 SBT contract를 작성해보자!
-------------
### SoulboundContract.sol 분석   
```
// SPDX-License-Identifier: MIT
pragma solidity ^0.8.4;

import "@openzeppelin/contracts/token/ERC721/ERC721.sol";
import "@openzeppelin/contracts/token/ERC721/extensions/ERC721URIStorage.sol";
import "@openzeppelin/contracts/access/Ownable.sol";

contract Soulbound is ERC721, ERC721URIStorage, Ownable {

    uint256 private _tokenIdCounter;

    constructor() ERC721("SoulBound", "SBT") {}

    function _beforeTokenTransfer(address from, address to, uint256 tokenId)
        internal
        override
    {
        require(from == address(0), "Token not transferable");
        super._beforeTokenTransfer(from, to, tokenId);
    }

    function safeMint(address to) public onlyOwner {
        _tokenIdCounter += 1;
        _safeMint(to, _tokenIdCounter);
    }

    // The following functions are overrides required by Solidity.

    function _burn(uint256 tokenId) internal override(ERC721, ERC721URIStorage) {
        super._burn(tokenId);
    }

    function tokenURI(uint256 tokenId)
        public
        view
        override(ERC721, ERC721URIStorage)
        returns (string memory)
    {
        return super.tokenURI(tokenId);
    }
}   
```
#### 주의!   
* contract는 솔바운드토큰 프로젝트 파일의 노드 폴더 프로젝트가 아닌, config.js가 존재하는 root 디렉토리에 contract폴더를 생성하여 그 안에 생성하여야 한다!   

```
// SPDX-License-Identifier: MIT
라이센스 식별자 법적인 내용 표현을 위해 사용
>> 주석으로 표현되기 때문에 없어도 컴파일에 문제가 없지만
상업적으로 이용시 법적으로 불리해질 수 있음
>> 주석의 규칙 1 내용!!

pragma solidity ^0.8.4;
사용하는 솔리디티 언어를 0.8.4버전으로 사용하라는 뜻
>>pragma는 컴파일러 제작업체가 고유하게 자신의 것으로
정의 할 수 있는 지시어 따라서 여기서는 pragma solidity 이렇게
붙어진 것이 하나라는 것
>> pragma는 만능이라는 뜻으로 이 뒤에 어떠한 일을 컴파일러
에게 맡기는 것
>>include와 차이점 : 함수, 클래스, 변수의 선언 또는 정의가
들어가있는 헤더 파일 사용

import "@openzeppelin/contracts/token/ERC721/ERC721.sol";
import "@openzeppelin/contracts/token/ERC721/extensions/ERC721URIStorage.sol";
import "@openzeppelin/contracts/access/Ownable.sol";
>> import는 해당 스크립트에서 사용할 모듈을 불러오는 기능

contract Soulbound is ERC721, ERC721URIStorage, Ownable {
>> Soulbound라는 컨트랙 정의부분,
>> ERC, ERC721URIstorage, Ownable 모듈을 상속받게다는 의미를 지님

uint256 private _tokenIdCounter;
>> 정수형 변수를 선언한다. 변수의 내용은 토큰의 아이디

constructor() ERC721("SoulBound", "SBT") {}
>> ERC721 컨트랙에 존재하는 생성자를 상속받아 soulBound라는 이름의 SBT 타입의 컨트랙 객체를 생성한다
>> 솔리디티에서 프로그램에 위에서 생성하는 객체는 무한정 만들어낼 수 없다
>> 왜????, 해당 객체는 컨트랙 내용을 가지고 있다. 그리고 컨트랙 내용은 모두가 볼 수 있는 네트워크, 블록체인에 올라가게 된다.
한 장소이지만 모두가 알아볼 수 있으니 각자 계약서를 가질 필요가 없는데 굳이 여러개 만들면, 블록체인 내의 기계들은 어떤 컨트랙을 사용하여햐 할지 모를거다
 
function _beforeTokenTransfer(address from, address to, uint256 tokenId)internal override
>> function 키워드는 솔리디티 언어에서 함수를 선언혹은 정의할 때 필요한 키워드이다
>> internal 키워드는 솔리디티 함수의 옵션중 접근제어 옵션이다. 해당 내용은 컨트랙 내부와 컨트랙을 상속한 자식 컨트랙만 접근이 가능
>> override 키워드는 해당 함수가 어떠한 함수를 오버라이드 했다는 의미이다. 즉, 부모에서 상속 받은 이름이 같은 함수를 재정의한 함수라고 할 수 있다.  

{
    require(from == address(0), "Token not transferable");
    super._beforeTokenTransfer(from, to, tokenId);
}
>> require은 예외처리 문구, 조건이 맞지 않으면 이전 상태로 되돌리는 롤백함수를 호출한다.
>> address(0)은 새 컨트랙이 발행되는 시작주소이다. require의 예외처리 조건은 보내는 객체의 주소가 자신의 주소와 컨트랙을 보낸 주소의 갯수에서 파생된 수가 0,
즉 다른 객체에게 컨트랙을 보낸 전적이 없으면 예외처리를한다

>> 해당 부분은 솔바운드 토큰의 양도 불가 특징을 구현하는 코드이다

>> super은 부모 컨트랙의 함수를 호출하는데 이때 부모 컨트랙의 지위와 동일한 권위를 같게된다.
해당 코드는 솔바운드 컨트랙의 부모인 ERC721의 _beforeTokenTransfer를 ERC721가 호출한 것처럼 호출한다
만약 ERC721._beforeTokenTransfer로 ERC721 함수를 호출하면 이것은 ERC721를 상속한 솔바운드 컨트랙이 호출한 것으로 처리한다.
>>_beforeTokenTransfer은 ERC721에 선언되어잇으며 가상함수로 선언되어 있고 정의 내용은 없다. 순수가상함수라고 추측할 수 있다.

>>해당 코드는 가상함수인 _beforeTokenTransfer를 재정의할 수 있도록 하는 코드로, 만약 존재하지 않는다면 빈 정의내용이 있는 함수를 쓰는 모양이라 아무 소용이 없게 된다

    function safeMint(address to) public onlyOwner {
        _tokenIdCounter += 1;
        _safeMint(to, _tokenIdCounter);
    }
>> onlyOwner라는 함수 수정자를 이용한 컨트랙을 직접 발행하는 함수이다 함수가 실행되기 전에 오너주소 존재 여부를 먼저 확인한다
>> 이후 토큰카운트 수를 올리고 ERC721에 존재하는 가상함수 safeMint를 호출한다
>> super를 사용하지 않는 이유는 

    function _burn(uint256 tokenId) internal override(ERC721, ERC721URIStorage) {
        super._burn(tokenId);
    }
>> 토큰을 없애는 코드이다

    function tokenURI(uint256 tokenId)
        public
        view
        override(ERC721, ERC721URIStorage)
        returns (string memory)
    {
        return super.tokenURI(tokenId);
    }
>> 토큰의 정보를 반환하는 코드이다

```
