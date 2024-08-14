# File: contact_service.py
# Author: Jesenia Roberts 
# Date: 7/15/2024
# Description: This class is meant to act as an adminstrative class 
# to the contact class. This will allow editing of the Contact class as 
# needed

# imports
import random
import string
from contact import Contact
from mongodb_client import MongoDbClient


# class definition
class ContactService:
    def __init__(self, client: MongoDbClient):
        self.client = client
        """Initializes the ContactService with an empty contact list and sets up for generating unique IDs."""
        # Initialize class instances using DataFrame
        contacts = {}

        """Retrieve the contacts from mongodb"""
        df = self.client.retrieve_contacts()
        if df is not None:
            for index, row in df.iterrows():
                contacts[row['contactID']] = Contact(row['contactID'],
                                                     row['firstName'],
                                                     row['lastName'],
                                                     row['phone'],
                                                     row['address'])
        self.contact_list = contacts

    # generates a random String ID for new contacts
    def generate_random_id(self):
        return ''.join(random.choices(string.ascii_letters + string.digits, k=8))

    # adds a new contact with a randomly generated ID and default values
    def add_contact(self, firstName, lastName, phone, address):
        contact_id = self.generate_random_id()
        while contact_id in self.contact_list:
            print(f"Generated contactID already exists, creating another.")
            contact_id = self.generate_random_id()
        contact = Contact(contact_id, firstName, lastName, phone, address)
        # Add it to reflect in the db
        self.client.add_contact(contact)
        self.contact_list[contact_id] = contact
        return contact_id

    # deletes a contact by ID
    def delete_contact(self, contact_id):
        if contact_id in self.contact_list:
            self.client.delete_contact(contact_id)
            del self.contact_list[contact_id]
        else:
            print(f"Error: Contact ID {contact_id} does not exist.")

    # updates the first name of a contact by ID
    def update_first(self, contact_id, first):
        if contact_id in self.contact_list:
            local_contact = self.contact_list[contact_id]
            local_contact.set_firstName(first)
            self.client.edit_contact(local_contact)
            self.contact_list[contact_id] = local_contact
        else:
            print(f"Error: Contact ID {contact_id} does not exist.")

    # updates the last name of a contact by ID
    def update_last(self, contact_id, last):
        if contact_id in self.contact_list:
            local_contact = self.contact_list[contact_id]
            local_contact.set_lastName(last)
            self.client.edit_contact(local_contact)
            self.contact_list[contact_id] = local_contact
        else:
            print(f"Error: Contact ID {contact_id} does not exist.")

    # updates the phone number of a contact by ID
    def update_phone_number(self, contact_id, phone_number):
        if contact_id in self.contact_list:
            local_contact = self.contact_list[contact_id]
            local_contact.set_phone(phone_number)
            self.client.edit_contact(local_contact)
            self.contact_list[contact_id] = local_contact
        else:
            print(f"Error: Contact ID {contact_id} does not exist.")

    # updates the address of a contact by ID
    def update_address(self, contact_id, address):
        if contact_id in self.contact_list:
            local_contact = self.contact_list[contact_id]
            local_contact.set_address(address)
            self.client.edit_contact(local_contact)
            self.contact_list[contact_id] = local_contact
        else:
            print(f"Error: Contact ID {contact_id} does not exist.")

    # retrieves a contact by ID
    def get_contact_by_id(self, contact_id):
        return self.contact_list.get(contact_id)

    def get_all_contacts(self):
        return self.contact_list.values()
