# File: mongodb_client.py
# Author: Jesenia Roberts
# Date: 8/9/2024
# Description: This class is the mongo db client
# used to abstract away mongo db CRUD operations
# when dealing with contacts
from pymongo import MongoClient
from contact import Contact
import pandas as pd


class MongoDbClient:
    def __init__(self):
        # Provide the mongodb atlas url to connect python to mongodb using pymongo
        self.connection_string = "mongodb://contactsuser:mongo123@localhost:27017/?authSource=contacts"

        # Create a connection using MongoClient. You can import MongoClient or use pymongo.MongoClient
        self.client = MongoClient(self.connection_string)

        # Create the database
        self.contacts_database = self.client['contacts']

        # Retrieve a collection named "contacts"
        self.collection_name = self.contacts_database["contacts"]

    def retrieve_contacts(self):
        item_details = self.collection_name.find()
        return pd.DataFrame(list(item_details))

    def add_contact(self, contact: Contact):
        self.collection_name.insert_one(
            {
                "contactID": contact.get_contactID(),
                "firstName": contact.get_firstName(),
                "lastName": contact.get_lastName(),
                "phone": contact.get_phone(),
                "address": contact.get_address()
            })

    def edit_contact(self, contact: Contact):
        query_filter = {'contactID': contact.get_contactID()}
        update_operation = {"$set":
            {
                "firstName": contact.get_firstName(),
                "lastName": contact.get_lastName(),
                "phone": contact.get_phone(),
                "address": contact.get_address()
            }
        }
        self.collection_name.update_one(query_filter, update_operation)

    def delete_contact(self, contact: Contact):
        self.collection_name.delete_one({"contactID": contact.get_contactID()})
