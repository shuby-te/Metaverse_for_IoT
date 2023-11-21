Create a SBT Step 004 - Create a SBT Test.js   
=============   
목표 : 테스트 스크립트가 무엇인지 확인하고 테스트 스크립트를 분석한다   
-------------   
```
const { expect } = require("chai");

describe("Soulbound Token Test", function () {
    let owner;

    beforeEach(async function () {
        // Retrieve the default account from ethers
        [owner] = await ethers.getSigners();

        // A helper to get the contracts instance and deploy it locally
        const Soulbound = await ethers.getContractFactory("Soulbound");
        soulbound = await Soulbound.deploy();

        // Mint token ID 1 to owner address
        await soulbound.safeMint(owner.address);
        
    });

    it("check the owner is correct", async () => {
        // Check that owner address owns the token ID 0
        const value = await soulbound.ownerOf(1);
        expect(value).to.equal(owner.address);
    });

    it("should revert when trying to transfer via safeTransferFrom", async () => {

        // Note that the approve function call will fail regardless
        const approve = await soulbound.approve("0x000000000000000000000000000000000000dEaD", 1)

        await expect(soulbound['safeTransferFrom(address,address,uint256)'](
            owner.address,
            "0x95222290DD7278Aa3Ddd389Cc1E1d165CC4BAfe5",
            1 // token id
        )).to.be.reverted;

    });

    it("should revert when trying to transfer via transferFrom", async () => {

        // Note that the approve function call will fail regardless
        const approve = await soulbound.approve("0x000000000000000000000000000000000000dEaD", 1)

        await expect(soulbound['transferFrom(address,address,uint256)'](
            owner.address,
            "0x95222290DD7278Aa3Ddd389Cc1E1d165CC4BAfe5",
            1 // token id
        )).to.be.reverted;
        
    });
});
```

```
const { expect } = require("chai");
>>

describe("Soulbound Token Test", function () {
>> describe는 테스트하는 객체라는 의미로 여러 테스트함수를 묶을때 사용한다
해당 테스트를 실행하면 Soulbound token Test라는 문구를 실행하고 테스트 함수를 실행한다

    let owner;
    >> 오너의 주소를 저장하는 변수이다. 변수는 let으로 선언된다.
    >> let은 변수타입으로 해당 변수가 존재하는 블럭만 유효한 범위이며 재선언이 불가능한다. 그러나 재할당은 가능하다 

    beforeEach(async function () {
    >> beforeEach는 모든 테스트 함수들이 실행되기 전에 실행하는 객체라는 것을 알려주는 키워드이다.
    >> async function은 비동기화 함수를 말한다. 즉 테스트 코드의 비동기화 함수들은 실행전에 beforeEach의 내용을 실행한다
 
        // Retrieve the default account from ethers
        [owner] = await ethers.getSigners();
        >> 이더.js라는 파일에 존재하는 getsigners로 주소를 반환해 owner에 저장한다. awit 키워드는 async에서 반환한 프라미스가 이행될때까지 기다리라는 의미를 가진다.
        >> getSigners는 매개변수값이 null이라면 주소를 0으로 설정한다

        // A helper to get the contracts instance and deploy it locally
        const Soulbound = await ethers.getContractFactory("Soulbound");
        >> Soulbound변수에 soulbound 컨트랙을 반환한다.
        soulbound = await Soulbound.deploy();
        >> Soulbound 변수는 ether타입을 가지고 있다. ether의 deploy함수를 실행해 그 값을 반환해 객체를 생성한다

        // Mint token ID 1 to owner address
        await soulbound.safeMint(owner.address);
        >> address를 반환해 토큰을 발행한다.
        
    });

    it("check the owner is correct", async () => {
        // Check that owner address owns the token ID 0
        const value = await soulbound.ownerOf(1);
        expect(value).to.equal(owner.address);
    });
    >> 토큰의 주인이 맞음을 확인하다

    it("should revert when trying to transfer via safeTransferFrom", async () => {

        // Note that the approve function call will fail regardless
        const approve = await soulbound.approve("0x000000000000000000000000000000000000dEaD", 1)

        await expect(soulbound['safeTransferFrom(address,address,uint256)'](
            owner.address,
            "0x95222290DD7278Aa3Ddd389Cc1E1d165CC4BAfe5",
            1 // token id
        )).to.be.reverted;

    });
    >> 토큰의 트랜스를 거부함을 확인함

    it("should revert when trying to transfer via transferFrom", async () => {

        // Note that the approve function call will fail regardless
        const approve = await soulbound.approve("0x000000000000000000000000000000000000dEaD", 1)

        await expect(soulbound['transferFrom(address,address,uint256)'](
            owner.address,
            "0x95222290DD7278Aa3Ddd389Cc1E1d165CC4BAfe5",
            1 // token id
        )).to.be.reverted;
    >> 토큰의 트랜스를 거부함을 확인함
        
    });
});
```
