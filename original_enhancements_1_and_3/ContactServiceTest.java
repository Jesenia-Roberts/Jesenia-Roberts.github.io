package module_3_milestone;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

class ContactServiceTest {

	@Test
	void testAddAndDelete() {
		ContactService contactService = new ContactService();
		contactService.addContact();
		assertTrue(contactService.getContactById("1") != null);
		contactService.deleteContact("1");
		assertTrue(contactService.getContactById("1") == null);
	}
	
	@Test
	void testUpdate() {
		ContactService contactService = new ContactService();
		contactService.addContact();
		contactService.updateFirst("1", "Jesenia");
		contactService.updateLast("1", "Roberts");
		contactService.updatePhoneNumber("1", "9788733040");
		contactService.updateAddress("1", "202 Rainy Street");
		
		Contact tester = contactService.getContactById("1");
		assertTrue(tester.getFirstName() == "Jesenia");
		assertTrue(tester.getLastName()== "Roberts");
		assertTrue(tester.getPhone() == "9788733040");
		assertTrue(tester.getAddress() == "202 Rainy Street" );
		
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			contactService.updateFirst("1", "jeseniataliaurbinaroberts");
		});
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			contactService.updateFirst("1", null);
		});	
		
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			contactService.updateLast("1", "jeseniataliaurbinaroberts");
		});
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			contactService.updateLast("1", null);
		});	
		
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			contactService.updatePhoneNumber("1", "1234567891011");
		});
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			contactService.updatePhoneNumber("1", null);
		});	
		
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			contactService.updateAddress("1", "202 VeryLongAddressThatWillCauseAnError Drive");
		});
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			contactService.updateAddress("1", null);
		});	
	}

}
