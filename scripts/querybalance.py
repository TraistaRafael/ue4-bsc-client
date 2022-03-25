import argparse
import json
import requests
from web3 import Web3

ADDRESS_LENGTH = 42
BSC_URL = "https://bsc-dataseed.binance.org/"
ETH_URL = "https://api.bscscan.com/api"

def QueryBalance(wallet, token):
    try:
        bsc = BSC_URL
        web3 = Web3(Web3.HTTPProvider(bsc))
        url_eth = ETH_URL
        contract_address = web3.toChecksumAddress(token)
        API_ENDPOINT = url_eth + "?module=contract&action=getabi&address=" + str(contract_address)
        r = requests.get(url = API_ENDPOINT)
        response = r.json()
        abi=json.loads(response["result"])

        contract = web3.eth.contract(address=contract_address, abi=abi)
        address = web3.toChecksumAddress(wallet)
        balance=contract.functions.balanceOf(address).call()
        return f"{balance / 1000000} {contract.functions.symbol().call()}"
    except:
        return "Query failed, unknown error"


def main():
    parser = argparse.ArgumentParser(description='Query BSC wallet balance')
    parser.add_argument('-wallet', type=str, help='Wallet address')
    parser.add_argument('-token', type=str, help='Token address')

    args = parser.parse_args()

    if len(args.wallet) != ADDRESS_LENGTH or args.wallet[0:2] != "0x":
        print("Bad wallet address.")
        return

    if len(args.token) != ADDRESS_LENGTH or args.token[0:2] != "0x":
        print("Bad token address.")
        return
    
    print(QueryBalance(args.wallet, args.token))

if __name__ == "__main__":
    main()


