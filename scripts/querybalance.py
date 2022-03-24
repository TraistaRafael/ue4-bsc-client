import argparse
import json
import requests
from web3 import Web3

parser = argparse.ArgumentParser(description='Query BSC wallet balance')
parser.add_argument('-wallet', type=str, help='Wallet address')
parser.add_argument('-token', type=str, help='Token address')

args = parser.parse_args()

bsc = "https://bsc-dataseed.binance.org/"
web3 = Web3(Web3.HTTPProvider(bsc))
url_eth = "https://api.bscscan.com/api"
contract_address = web3.toChecksumAddress(args.token)
API_ENDPOINT = url_eth + "?module=contract&action=getabi&address=" + str(contract_address)
r = requests.get(url = API_ENDPOINT)
response = r.json()
abi=json.loads(response["result"])

contract = web3.eth.contract(address=contract_address, abi=abi)
address = web3.toChecksumAddress(args.wallet)
balance=contract.functions.balanceOf(address).call()

print (f"{balance / 1000000} {contract.functions.symbol().call()}")
