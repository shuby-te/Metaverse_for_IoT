Create a SBT 005 - Depoly   
=============   
목표 : 발행 스크립트를 만들고 발행해보자   
```
// Import the Hardhat library
const hre = require("hardhat");

// Define an async function to handle deployment
async function deploy() {
    // Obtain the Soulbound contract
    const Soulbound = await hre.ethers.getContractFactory("Soulbound");
    // Deploy the Soulbound contract
    const soulbound = await Soulbound.deploy();

    // wait for the transaction to mine
    await soulbound.waitForDeployment()

    // Log the deployed contract's address
    console.log("Soulbound token deployed at:", soulbound.target);
}

deploy()
    .then(() => console.log("Deployment complete"))
    .catch((error) => console.error("Error deploying contract:", error));
```
