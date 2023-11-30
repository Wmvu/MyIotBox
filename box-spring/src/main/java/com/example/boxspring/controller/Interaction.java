package com.example.boxspring.controller;

import com.example.boxspring.contract.SolidityERC721;
import com.example.boxspring.controller.intercpor.Result;
import com.example.boxspring.mapper.UserMapper;
import com.example.boxspring.pojo.User;
import com.example.boxspring.utils.TokenUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import org.web3j.abi.FunctionEncoder;
import org.web3j.abi.datatypes.Function;
import org.web3j.abi.datatypes.Type;
import org.web3j.crypto.Credentials;
import org.web3j.protocol.Web3j;
import org.web3j.protocol.core.RemoteFunctionCall;
import org.web3j.protocol.core.methods.request.Transaction;
import org.web3j.protocol.core.methods.response.EthEstimateGas;
import org.web3j.protocol.core.methods.response.TransactionReceipt;
import org.web3j.tx.gas.ContractGasProvider;
import org.web3j.tx.gas.StaticGasProvider;

import java.io.IOException;
import java.math.BigInteger;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

@RestController
@RequestMapping("/api")
public class Interaction {
    @Autowired
    private Web3j web3j;
    @Autowired
    UserMapper userMapper;
    // 钱包私钥
    private static String walletKey = "c937eb1505e73e396641caf75d4c3e6f2e9cbe0632e053c15ea6f817db30f7e2";
    // 合约地址
    private static String contractAddress = "0x564FCdB3a585871F8C25CcF9cc73a6846EC833D5";
    private static Credentials credentials ;
    private static BigInteger gasPrice ;
    private static ContractGasProvider contractGasProvider ;

    @GetMapping("/gas")
    public String GetGas() throws IOException {
        BigInteger gas = web3j.ethGasPrice().send().getGasPrice();
        return gas.toString();
    }
    @GetMapping("/name")
    public String GetContractname() throws Exception {
        Credentials credentials = Credentials.create(walletKey);
        BigInteger gasPrice = web3j.ethGasPrice().send().getGasPrice();System.out.println(gasPrice);
        SolidityERC721 myBox = SolidityERC721.load(contractAddress,web3j,credentials,gasPrice,BigInteger.valueOf(15_000));
        RemoteFunctionCall<String> tr = myBox.name();
        return tr.send();
    }
    @GetMapping("/rsmint")
    public Result rsmint() throws Exception {
        User s =  TokenUtils.getCurrentUser();
        String privatekey = userMapper.getKey(s.getWeb3user());
        credentials = Credentials.create(privatekey);
        gasPrice = web3j.ethGasPrice().send().getGasPrice();
        BigInteger gasLimit = getGaslimit("rsmint", web3j, credentials.getAddress(), contractAddress);
         contractGasProvider = new StaticGasProvider(gasPrice,gasLimit);
        SolidityERC721 myBox = SolidityERC721.load(contractAddress,web3j,credentials,contractGasProvider);
        RemoteFunctionCall<TransactionReceipt> t = myBox.rsmint();
        TransactionReceipt hst = t.send();
//        return hst.getTransactionHash();
       return Result.success(hst.getTransactionHash());
    }
    @GetMapping("/open")
    public Result open() throws Exception {
        User s =  TokenUtils.getCurrentUser();
        String privatekey = userMapper.getKey(s.getWeb3user());
        credentials = Credentials.create(privatekey);
        gasPrice = web3j.ethGasPrice().send().getGasPrice();
        BigInteger gasLimit = getGaslimit("open", web3j, credentials.getAddress(), contractAddress);
        contractGasProvider = new StaticGasProvider(gasPrice,gasLimit);
        SolidityERC721 myBox = SolidityERC721.load(contractAddress,web3j,credentials,contractGasProvider);
        RemoteFunctionCall<TransactionReceipt> t = myBox.open();
        TransactionReceipt hst = t.send();
        return Result.success(hst.getTransactionHash());
    }
@GetMapping("/isopen")
    public Boolean isopen() throws Exception {
        init();
        SolidityERC721 myBox = SolidityERC721.load(contractAddress,web3j,credentials,contractGasProvider);
        Boolean flag = myBox.isopen(BigInteger.ZERO).send();
        return flag;
    }

    public BigInteger getGaslimit(String cname,Web3j web3,String Address,String contractAddress) throws IOException {
        String function = cname;
        List<Type> inputParams = Arrays.asList();

        Function contractFunction = new Function(function, inputParams, Collections.emptyList());

        EthEstimateGas ethEstimateGas = web3.ethEstimateGas(
                Transaction.createEthCallTransaction(
                        Address,
                        contractAddress,
                        FunctionEncoder.encode(contractFunction)
                )
        ).send();

        if (ethEstimateGas.hasError()) {
            // 处理发生的错误
//            System.out.println("获取 gas 上限时发生错误: " + ethEstimateGas.getError().getMessage());
            return BigInteger.valueOf(150_000);
        } else {
            BigInteger gasLimit = ethEstimateGas.getAmountUsed();
//            System.out.println("动态获取的 gas 上限: " + gasLimit);
            return gasLimit;
        }
    }
    private void init() throws IOException {
         credentials = Credentials.create(walletKey);
         gasPrice = web3j.ethGasPrice().send().getGasPrice();
         contractGasProvider = new StaticGasProvider(gasPrice,BigInteger.ONE);
    }
    @GetMapping("Web3Address")
    public String Web3address(){

        return "";
    }
}
