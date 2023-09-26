package com.example.Issuer;

import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;

import org.hyperledger.indy.sdk.wallet.Wallet;
import org.hyperledger.indy.sdk.did.Did;
import org.hyperledger.indy.sdk.did.DidJSONParameters;
import org.hyperledger.indy.sdk.did.DidResults.CreateAndStoreMyDidResult;
import org.hyperledger.indy.sdk.pool.Pool;
import org.hyperledger.indy.sdk.ledger.Ledger;

import org.json.JSONObject;

@SpringBootApplication
public class Main {

	public static void main(String[] args) throws Exception {
		SpringApplication.run(Main.class, args);
		System.out.println("Hello World");

		String walletName = new JSONObject().put("id", "wallet").toString();
		String walletKey = new JSONObject().put("key", "1234").toString();
		Wallet.createWallet(walletName, walletKey).get();

		Wallet wallet = Wallet.openWallet(walletName, walletKey).get();

		DidJSONParameters.CreateAndStoreMyDidJSONParameter didJson = new DidJSONParameters.CreateAndStoreMyDidJSONParameter(
				null, "issuer00000000000000000000000000", null, null);
		CreateAndStoreMyDidResult didResult = Did.createAndStoreMyDid(wallet, didJson.toJson()).get();
		didResult.getDid();
		didResult.getVerkey();

		CreateAndStoreMyDidResult didNewResult = Did.createAndStoreMyDid(wallet, "{}").get();
		didNewResult.getDid();
		didNewResult.getVerkey();

		Pool.setProtocolVersion(2).get();
		
		String dir = System.getProperty("user.dir");
		String poolPath = new JSONObject("genesis_txn", dir + "pool_transactions_genesis").toString();
		Pool.createPoolLedgerConfig("sandbox", poolPath).get();

		Pool pool = Pool.openPoolLedger("sandbox", "{}").get();

		String nymRequest = Ledger.buildGetNymRequest(didResult.getDid(), "FdjncozbMFZP4YvZbqET2y").get();

		String nymRespone = Ledger.signAndSubmitRequest(pool, wallet, didResult.getDid(), nymRequest).get();

		nymRequest = Ledger.buildNymRequest(didResult.getDid(), didNewResult.getDid(), didNewResult.getVerkey(), null, null).get();

		nymRespone = Ledger.signAndSubmitRequest(pool, wallet, didResult.getDid(), nymRequest).get();
		System.out.println("nymRespone :" + nymRespone);

		wallet.closeWallet().get();
		Wallet.deleteWallet(walletName, walletKey).get();

		
	}

	@Bean
	public CommandLineRunner commandLineRunner() {
		return args -> {
			System.out.println("Hello World");
			
			String dir = System.getProperty("user.dir");
			System.out.println("current dir = " + dir);
		};
	}

}
