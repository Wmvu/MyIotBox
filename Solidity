// SPDX-License-Identifier: Mybox
pragma solidity ^0.8.20;

import "@openzeppelin/contracts/token/ERC721/ERC721.sol";
import "@openzeppelin/contracts/access/Ownable.sol";

contract Mybox is ERC721, Ownable {
    uint8 Value;
    uint8 MAX = 1;
    constructor()
        ERC721("MyIotbox", "MIb")
        Ownable(msg.sender)
    {}
    function safeMint(address to) public onlyOwner {
        require(Value < MAX,"this NFT already MAX value");
        _safeMint(to, Value);
        Value ++;
    }

    function otransfer(address to, uint256 tokenId) public onlyOwner {
        _transfer(_ownerOf(tokenId),to,tokenId);
    }

    function rsmint() public {
        require(_ownerOf(0) == address(this) ,"temporary not NFT");
        _transfer(address(this),msg.sender,0);
    }
    function open() public {
        require(_ownerOf(0) == msg.sender ,"You not this NFT");
        _transfer(msg.sender,address(this),0);
    }
    function _baseURI() internal pure override returns (string memory) {
        return "ipfs://Qmf651gUzoNUnqamxTv9N78gRLe3sU2yvfHhib3Xsd1wXE";
    }
    function setNum(uint8 m) public onlyOwner{
        MAX = m;
    }

    function tokennft(uint256 _id) view public returns(address)
    {
        _requireOwned(_id);
        return _ownerOf(_id);
    }
    
    function isopen(uint8 i) view public returns(bool){
        return _ownerOf(i)==address(this)?true:false;
    }

}
