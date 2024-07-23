# File: Contact.py
# Author: Jesenia Roberts 
# Date: 7/15/2024
# Description: This class is meant to act as an adminstrative class 
# to the contact class. This will allow editing of the Contact class as 
# needed

# imports
import random
import string
from contact import Contact

# class definition
class ContactService:
    def __init__(self):
        """Initializes the ContactService with an empty contact list and sets up for generating unique IDs."""
        self.contact_list = {}

    # generates a random String ID for new contacts
    def generate_random_id(self):
        return ''.join(random.choices(string.ascii_letters + string.digits, k=8))

    # adds a new contact with a randomly generated ID and default values
    def add_contact(self):
        contact_id = self.generate_random_id()
        contact = Contact(contact_id, "", "", "0000000000", "")
        self.contact_list[contact_id] = contact
        return contact_id
   
    # deletes a contact by ID
    def delete_contact(self, contact_id):
        if contact_id in self.contact_list:
            del self.contact_list[contact_id]
        else:
            print(f"Error: Contact ID {contact_id} does not exist.")

    # updates the first name of a contact by ID
    def update_first(self, contact_id, first):
        if contact_id in self.contact_list:
            self.contact_list[contact_id].set_firstName(first)
        else:
            print(f"Error: Contact ID {contact_id} does not exist.")

    # updates the last name of a contact by ID
    def update_last(self, contact_id, last):
        if contact_id in self.contact_list:
            self.contact_list[contact_id].set_lastName(last)
        else:
            print(f"Error: Contact ID {contact_id} does not exist.")

    # updates the phone number of a contact by ID
    def update_phone_number(self, contact_id, phone_number):
        if contact_id in self.contact_list:
            self.contact_list[contact_id].set_phone(phone_number)
        else:
            print(f"Error: Contact ID {contact_id} does not exist.")

    # updates the address of a contact by ID
    def update_address(self, contact_id, address):
        if contact_id in self.contact_list:
            self.contact_list[contact_id].set_address(address)
        else:
            print(f"Error: Contact ID {contact_id} does not exist.")

    # retrieves a contact by ID
    def get_contact_by_id(self, contact_id):
        return self.contact_list.get(contact_id)
