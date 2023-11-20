package com.example.Issuer;

import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;

import org.hyperledger.indy.sdk.wallet.Wallet;

import java.io.File;

import org.hyperledger.indy.sdk.anoncreds.Anoncreds;
import org.hyperledger.indy.sdk.anoncreds.AnoncredsResults;
import org.hyperledger.indy.sdk.did.Did;
import org.hyperledger.indy.sdk.did.DidJSONParameters;
import org.hyperledger.indy.sdk.did.DidResults.CreateAndStoreMyDidResult;
import org.hyperledger.indy.sdk.pool.Pool;
import org.hyperledger.indy.sdk.pool.PoolJSONParameters;
import org.hyperledger.indy.sdk.ledger.Ledger;
import org.json.JSONArray;
import org.json.JSONObject;

@SpringBootApplication
public class Main {

	public static void main(String[] args) throws Exception {
		SpringApplication.run(Main.class, args);
		System.out.println("Hello World");

		System.setProperty("jna.library.path", "lib/");

		System.out.println("Wallet Create");
		String walletName = new JSONObject().put("id", "wallet-test").toString();
		String walletKey = new JSONObject().put("key", "1234").toString();
		Wallet.createWallet(walletName, walletKey).get();

		System.out.println("Wallet Open");
		Wallet wallet = Wallet.openWallet(walletName, walletKey).get();

		DidJSONParameters.CreateAndStoreMyDidJSONParameter didJson = new DidJSONParameters.CreateAndStoreMyDidJSONParameter(
				null, "issuer00000000000000000000000000", null, null);
		CreateAndStoreMyDidResult didResult = Did.createAndStoreMyDid(wallet, didJson.toJson()).get();
		System.out.println("1 did:" + didResult.getDid());
		System.out.println("1 verkey:" + didResult.getVerkey());

		CreateAndStoreMyDidResult didNewResult = Did.createAndStoreMyDid(wallet, "{}").get();
		System.out.println("2 did:" + didNewResult.getDid());
		System.out.println("2 verkey:" + didNewResult.getVerkey());

		Pool.setProtocolVersion(2).get();
		
		String dir = System.getProperty("user.dir");
		String poolPath = dir + "/pool_transactions_genesis";
		PoolJSONParameters.CreatePoolLedgerConfigJSONParameter createPoolLedgerConfigJSONParameter = 
			new PoolJSONParameters.CreatePoolLedgerConfigJSONParameter(poolPath);
		Pool.createPoolLedgerConfig("sandbox", createPoolLedgerConfigJSONParameter.toJson()).get();
		System.out.println("Pool Config Created");

		Pool pool = Pool.openPoolLedger("sandbox", "{}").get();
		System.out.println("Pool Open");

		String nymRequest = Ledger.buildGetNymRequest(didResult.getDid(), "FdjncozbMFZP4YvZbqET2y").get();

		String nymRespone = Ledger.signAndSubmitRequest(pool, wallet, didResult.getDid(), nymRequest).get();
		System.out.println("nymRespone :" + nymRespone);

		nymRequest = Ledger.buildNymRequest(didResult.getDid(), didNewResult.getDid(), didNewResult.getVerkey(), null, null).get();

		nymRespone = Ledger.signAndSubmitRequest(pool, wallet, didResult.getDid(), nymRequest).get();
		System.out.println("nymRespone :" + nymRespone);

		System.out.println("=== Schema Create ===");
		String schemaName = "test";
		String schemaVersion = "1.0";
		String scheamAtribute = new JSONArray().put("name").put("age").toString();

	    AnoncredsResults.IssuerCreateSchemaResult schemaResult = 
			Anoncreds.issuerCreateSchema(didResult.getDid(), schemaName, schemaVersion, scheamAtribute).get();
		String schemaId = schemaResult.getSchemaId();
		String schemaJson = schemaResult.getSchemaJson();
		System.out.println("schemaJson :" + schemaJson);

		String schemaRequest = Ledger.buildSchemaRequest(didResult.getDid(), schemaJson).get();
		String schemaRespone = Ledger.signAndSubmitRequest(pool, wallet, didResult.getDid(), schemaRequest).get();
		System.out.println("schemaRespone :" + schemaRespone);

		System.out.println("=== Cred Def Create ===");

		String credDefTag = "TAG1";
		AnoncredsResults.IssuerCreateAndStoreCredentialDefResult credentialDefResult = 
			Anoncreds.issuerCreateAndStoreCredentialDef(wallet, didResult.getDid(), schemaJson, credDefTag, null, null).get();

		String credDefId = credentialDefResult.getCredDefId();
		String credDefJson = credentialDefResult.getCredDefJson();
		System.out.println("credDefJson :" + credDefJson);

		String credDefRequest = Ledger.buildCredDefRequest(didResult.getDid(), credDefJson).get();
		String credDefRespone = Ledger.signAndSubmitRequest(pool, wallet, didResult.getDid(), credDefRequest).get();
		System.out.println("credDefRespone :" + credDefRespone);

		wallet.closeWallet().get();
		Wallet.deleteWallet(walletName, walletKey).get();

		pool.closePoolLedger().get();
		Pool.deletePoolLedgerConfig("sandbox").get();
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
