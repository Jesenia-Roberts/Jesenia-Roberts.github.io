import pytest
from contact import Contact
from contact_service import ContactService

class TestContactService:
    #contact = Contact("0", "first", "last", "0123456789", "address")
    #assert contact.get_contact_id() == "0"
    #assert contact.get_first_name() == "first"
    #assert contact.get_last_name() == "last"
    #assert contact.get_phone() == "0123456789"
    #assert contact.get_address() == "address"

    def test_contact_invalid_id(self):
        with pytest.raises(ValueError):
            Contact("12345678910", "first", "last", "0123456789", "address")
        with pytest.raises(ValueError):
            Contact(None, "first", "last", "0123456789", "address")

    def test_contact_invalid_first_name(self):
        with pytest.raises(ValueError):
            Contact("0", "jeseniataliaurbinaroberts", "last", "0123456789", "address")
        with pytest.raises(ValueError):
            Contact("0", None, "last", "0123456789", "address")

    def test_contact_invalid_last_name(self):
        with pytest.raises(ValueError):
            Contact("0", "first", "jeseniataliaurbinaroberts", "0123456789", "address")
        with pytest.raises(ValueError):
            Contact("0", "first", None, "0123456789", "address")

    def test_contact_invalid_phone_number(self):
        with pytest.raises(ValueError):
            Contact("0", "first", "last", "012345678", "address")
        with pytest.raises(ValueError):
            Contact("0", "first", "last", None, "address")

    def test_contact_invalid_address(self):
        with pytest.raises(ValueError):
            Contact("0", "first", "last", "0123456789", "202 VeryLongAddressThatWillCauseAnError Drive")
        with pytest.raises(ValueError):
            Contact("0", "first", "last", "0123456789", None)
