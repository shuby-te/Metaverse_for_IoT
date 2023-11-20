error   
=============   
```
PS C:\Users\user\soulbound-tokens> npx hardhat run --network goerli scripts/deploy.js
Error deploying contract: ProviderError: insufficient funds for gas * price + value: balance 0, tx cost 3255415224415614, overshot 3255415224415614
    at HttpProvider.request (C:\Users\user\soulbound-tokens\node_modules\hardhat\src\internal\core\providers\http.ts:88:21)
    at processTicksAndRejections (node:internal/process/task_queues:95:5)
    at HardhatEthersSigner.sendTransaction (C:\Users\user\soulbound-tokens\node_modules\@nomicfoundation\hardhat-ethers\src\signers.ts:125:18)
    at ContractFactory.deploy (C:\Users\user\soulbound-tokens\node_modules\ethers\src.ts\contract\factory.ts:111:24)
    at deploy (C:\Users\user\soulbound-tokens\scripts\deploy.js:9:23)
```
