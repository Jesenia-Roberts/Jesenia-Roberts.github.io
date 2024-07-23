# File: Contact.py
# Author: Jesenia Roberts 
# Date: 7/15/2024
# Description: This class is meant to hold all the necessary details of a contact
# including contactID, firstName, lastName, phone, and address
# as well as allow these variables to be accessed and manipulated

# class definition 
class Contact:
    def __init__(self, contactID, firstName, lastName, phone, address):
        if contactID is None or len(contactID) > 10:
            raise ValueError("Invalid ID")
        if firstName is None or len(firstName) > 10:
            raise ValueError("Invalid first name")
        if lastName is None or len(lastName) > 10:
            raise ValueError("Invalid last name")
        if phone is None or len(phone) != 10:
            raise ValueError("Invalid phone number")
        if address is None or len(address) > 30:
            raise ValueError("Invalid address")
        
        self.contactID = contactID
        self.firstName = firstName
        self.lastName = lastName
        self.phone = phone
        self.address = address
    
    # accessor methods
    def get_contactID(self):
        return self.contactID
    
    def get_firstName(self):
        return self.firstName
    
    def get_lastName(self):
        return self.lastName
    
    def get_phone(self):
        return self.phone
    
    def get_address(self):
        return self.address
    
    # mutator methods
    def set_firstName(self, firstName):
        if firstName is None or len(firstName) > 10:
            raise ValueError("Invalid first name")
        self.firstName = firstName
    
    def set_lastName(self, lastName):
        if lastName is None or len(lastName) > 10:
            raise ValueError("Invalid last name")
        self.lastName = lastName
    
    def set_phone(self, phone):
        if phone is None or len(phone) != 10:
            raise ValueError("Invalid phone number")
        self.phone = phone
    
    def set_address(self, address):
        if address is None or len(address) > 30:
            raise ValueError("Invalid address")
        self.address = address
