import pytest
from contact import Contact
from contact_service import ContactService

class TestContact:
    def test_valid_init(self):
        contactId = "1"
        firstName = "first name"
        lastName = "last name"
        phone = "1234567890"
        address = "some address"
        contact = Contact(contactId, firstName, lastName, phone, address)

        #Verify
        assert contact.get_contactID() == contactId
        assert contact.get_firstName() == firstName
        assert contact.get_lastName() == lastName
        assert contact.get_phone() == phone
        assert contact.get_address() == address

    def test_init_with_none(self):
        with pytest.raises(ValueError, match="Invalid ID"):
            Contact(None, None, None, None, None)

    def test_add_and_delete(self):
        contactService = ContactService()
        contactId = contactService.add_contact()

        assert contactService.get_contact_by_id(contact_id=contactId) is not None
        contactService.delete_contact(contact_id=contactId)
        assert contactService.get_contact_by_id(contact_id=contactId) is None

    def test_update(self):
        contact_service = ContactService()
        contactId = contact_service.add_contact()
        contact_service.update_first(contactId, "Jesenia")
        contact_service.update_last(contactId, "Roberts")
        contact_service.update_phone_number(contactId, "9788733040")
        contact_service.update_address(contactId, "202 Rainy Street")

        tester = contact_service.get_contact_by_id(contactId)
        assert tester.get_firstName() == "Jesenia"
        assert tester.get_lastName() == "Roberts"
        assert tester.get_phone() == "9788733040"
        assert tester.get_address() == "202 Rainy Street"

        with pytest.raises(ValueError):
            contact_service.update_first(contactId, "jeseniataliaurbinaroberts")
        with pytest.raises(ValueError):
            contact_service.update_first(contactId, None)

        with pytest.raises(ValueError):
            contact_service.update_last(contactId, "jeseniataliaurbinaroberts")
        with pytest.raises(ValueError):
            contact_service.update_last(contactId, None)

        with pytest.raises(ValueError):
            contact_service.update_phone_number(contactId, "1234567891011")
        with pytest.raises(ValueError):
            contact_service.update_phone_number(contactId, None)

        with pytest.raises(ValueError):
            contact_service.update_address(contactId, "202 VeryLongAddressThatWillCauseAnError Drive")
        with pytest.raises(ValueError):
            contact_service.update_address(contactId, None)
