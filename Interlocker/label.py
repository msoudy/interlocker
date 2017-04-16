#!/usr/bin/env python

import boto3
import pprint
import argparse


# furniture type:
# BOOKSHELF, BABY BED, SHOE RACK, BENCH, SOFA, CHAIR

def detect_labels(f):
    with open(f, 'rb') as image:
        response = client.detect_labels(Image={'Bytes': image.read()})
        # pprint.pprint(response['Labels'][0]['Name'])
        for each_list in response['Labels']:
            if each_list['Confidence'] >= 80:
                if each_list['Name'] == "Shelf" or each_list['Name'] == "Bookcase" or each_list['Name'] == "Book":
                    print "Bookshelf"
                elif each_list['Name'] == "Chair":
                    print "Chair"
                elif each_list['Name'] == "Shoe":
                    print "Shoe Rack"
                elif each_list['Name'] == "Bench":
                    print "Bench"
                elif each_list['Name'] == "Couch" or each_list['Name'] == "Sofa":
                    print "Couch"
                elif each_list['Name'] == "Cradle" or each_list['Name'] == "Crib" or each_list['Name'] == "Bed":
                    print "Baby Bed"
                # else:
                    # print each_list['Name']

        # pprint.pprint(response['Labels'])

if __name__ == "__main__":
    # parse arguments
    parser = argparse.ArgumentParser()
    parser.add_argument("-f", "--image", help="image file (png or jpg)", required=True)
    # parser.add_argument("-c", "--collection", help="rekognition collection id", default='snerted')
    # parser.add_argument("-r", "--region", help="aws region", default='us-east-1')
    args = parser.parse_args()

    client = boto3.client('rekognition', region_name='us-east-1')

    detect_labels(args.image)