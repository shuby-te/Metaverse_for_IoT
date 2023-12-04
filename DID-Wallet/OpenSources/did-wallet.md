# did-wallet

이 오픈 소스는 자바스크립트 언어를 기반으로 작성된 did wallet으로, 키에 대한 여러 기능들(잠금, 잠금해제, 키 추출, 키 추가 등)을 구현하고 이를 테스트할 수 있는 코드들로 구성되어 있다.

## DIDWallet class
did wallet을 구현하는 클래스로, 키를 암호화하는 lock(), 키를 복호화하는 unlock(), 키를 추가하는 addKey(), 태그에 맞는 키를 추출하는 extractByTags(), 잠긴 키를 반환하는 export() 기능들이 정의되어 있다.

    const crypto = require("crypto");   //이름에 해당되는 라이브러리 및 모델을 가져옴
    const base64url = require("base64url");
    const _ = require("lodash");
    const keyToKID = require("./keyToKID");
    
    const schema = require("./schema");
    
    class DIDWallet {   //did wallet을 나타내는 클래스로, 지갑에 대한 다양한 기능을 정의
      constructor(data = {}) {     //생성자
        let keys = [];
        if (typeof data === "string") {   //입력값이 문자열이라면 입력값을 ciphered속성(암호화된 키를 저장하는 속성)에 저장후 리턴
          this.ciphered = data;
          return;
        }
        if (data.keys) {  //입력값의 keys속성이 존재한다면 다음의 블럭을 실행
          keys = data.keys.map(k => {   //keys 속성의 키들을 키 유형에 맞게 가공하여 keys변수에 저장
            schema.validator.validate(k, schema.schemas.didWalletKey, {   //schema 모듈을 사용하여 키의 유효성을 검사
              throwError: true
            });
            switch (k.type) {   //키의 유형에 따라 키 식별자(kid)를 생성
              case "assymetric":
                return {
                  ...k,
                  kid: keyToKID(k.publicKey)
                };
              case "mnemonic":
                return {
                  ...k,
                  kid: keyToKID(k.mnemonic)
                };
            }
          });
        }
        this.keys = _.keyBy(keys, "kid"); //this.keys속성에 가공된 키들을 저장
      }
    
      lock(password) {  //비밀번호값을 입력으로 받아 지갑에 저장된 키를 잠그는(암호화하는) 함수
        let key = password;
        if (Object.keys(this.keys).length === 0) {    //this.keys속성에 저장된 키가 없다면 빈 지갑을 잠글 수 없다는 에러를 발생시킴
          throw new Error("Cannot lock an empty wallet.");
        }
        const plaintext = JSON.stringify(this.keys);  //this.keys속성의 데이터를 JSON문자열로 직렬화시킨 뒤, 이를 AES-256 암호로 암호화하여 this.ciphered속성에 저장
        let encrypt = crypto.createCipher("aes256", key);
        let encrypted = encrypt.update(plaintext, "utf8", "hex");
        encrypted += encrypt.final("hex");
        this.ciphered = base64url.encode(Buffer.from(encrypted, "hex"));
        delete this.keys;   //this.keys속성(암호화 전의 데이터)을 삭제
      }
    
      addKey(key) {   //키를 입력으로 받아 키를 지갑에 추가하는 함수
        if (!this.keys) {   //this.keys속성이 존재하지 않으면 지갑이 잠겨있는 것이므로 에러를 발생시킴
          throw new Error(
            "Cannot addKey to a ciphered wallet. You must unlock first."
          );
        }
    
        schema.validator.validate(key, schema.schemas.didWalletKey, {   //추가하고자 하는 키의 유효성을 검사
          throwError: true
        });
    
        let update = {};
    
        switch (key.type) {   //생성자와 동일하게 키 유형에 따라 키 식별자를 생성한 뒤 this.keys속성에 추가
          case "assymetric":
            update = {
              ...key,
              kid: keyToKID(key.publicKey)
            };
            break;
          case "mnemonic":
            update = {
              ...key,
              kid: keyToKID(key.mnemonic)
            };
            break;
        }
    
        this.keys = {
          ...this.keys,
          [update.kid]: update
        };
      }
    
      unlock(password) {  //password를 입력으로 받아 잠긴(암호화된) 키를 잠금해제(복호화)하는 함수
        let key = password;
        let decrypt = crypto.createDecipher("aes256", key);   //AES256 암호와 비밀번호를 이용해서 복호화한 뒤, JSON객체로 파싱하여 this.keys속성에 저장
        const ciphertext = base64url.toBuffer(this.ciphered).toString("hex");
        let decrypted = decrypt.update(ciphertext, "hex", "utf8");
        decrypted += decrypt.final();
        this.keys = JSON.parse(decrypted);
        delete this.ciphered;   //필요없어진 this.ciphered속성은 삭제
      }
    
      extractByTags(tags) {   //특정 태그를 가진 키들을 추출하는 함수
        if (!this.keys) {   //this.keys가 존재하지 않으면 키가 암호화되어 있는 것이므로 에러를 발생시킴
          throw new Error(
            "Cannot extractByTags from a ciphered wallet. You must unlock first."
          );
        }
        let keys = _.pickBy(this.keys, k => {   //this.keys에 저장된 키들에 대하여 입력으로 받은 태그와 일치하는 키들을 keys변수에 저장
          return _.intersection(k.tags, tags).length;
        });
        return _.values(keys);  //추출해낸 키들을 반환
      }
    
      export() {    //잠겨 있는 지갑을 반환하는 함수 (정확히는 지갑이 아닌 암호화된 키들을 반환)
        if (this.keys) {    //this.keys가 존재한다면 이는 잠긴 상태가 아니므로 에러를 발생시킴
          throw new Error("Cannot export plaintext wallet. You must lock first.");
        }
        return this.ciphered;   //암호화된 키들이 저장된 this.ciphered속성을 반환
      }
    }
    
    module.exports = DIDWallet;   //모듈이 함수를 내보내도록하여 다른 코드에서 이 함수를 사용할 수 있도록함

## index.js
DIDWallet 클래스의 객체(인스턴스)를 생성하는 create함수를 정의하는 코드이다. DIDWallet을 모듈로 가져와 함수를 정의한 뒤, module.export를 통해 함수를 내보내어 다른 코드에서 함수를 사용할 수 있도록 하였다.

    //DIDWallet 클래스의 인스턴스를 생성하고 관리하기 위한 함수를 정의하는 코드
    
    const DIDWallet = require("./DIDWallet");   //DIDWallet 모듈을 가져옴
    
    const create = data => {  //DIDWallet 클래스의 인스턴스를 생성하는 create함수를 정의
      return new DIDWallet(data);
    };
    
    module.exports = {  //모듈이 함수를 내보내도록하여 다른 코드에서 이 함수를 사용할 수 있도록함
      create
    };

## keyToKID.js
키의 유형에 따라 공개키에 대한 식별자(kid)의 존재 여부가 다를 수 있기 때문에 유형에 맞춰 키 식별자를 생성하기 위한 함수가 keyToKID.js에 정의되어 있다. kid가 존재하는 유형의 경우 그대로 반환하며, 그렇지 않은 경우 SHA-256 해시함수로 공개키를 해시한 값을 가공하여 반환한다.

    //공개키를 입력으로 받아 공개키에 대한 식별자(kid)를 만들어 반환하는 함수를 정의하는 코드
    
    const crypto = require("crypto");
    const base64url = require("base64url");
    
    module.exports = publicKey => {   //publicKey를 입력으로 받는 함수를 정의 (그런 다음 해당 함수를 모듈로 내보내어 다른 코드에서 사용할 수 있도록 함)
      try {
        const jwk = JSON.parse(publicKey);  //publicKey를 JSON객체로 파싱한 뒤, kid속성이 있다면 kid속성을 반환 (이미 존재하는 키 식별자일 경우의 처리)
        if (jwk.kid) {
          return jwk.kid;
        }
      } catch (e) {
        // do nothing
      }
      return base64url.encode(  //파싱에 실패하거나 kid속성이 존재하지 않는 경우, publicKey를 해시 함수로 해시한 후 base64url형식으로 인코딩한 값을 반환
        crypto
          .createHash("sha256")
          .update(Buffer.from(publicKey))
          .digest()
      );
    };












