package module_3_milestone;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

class ContactTest {

	@Test
	void testContact() {
		Contact contact = new Contact("0", "first", "last", "0123456789", "address");
		assertTrue(contact.getContactID().equals("0"));
		assertTrue(contact.getFirstName().equals("first"));
		assertTrue(contact.getLastName().equals("last"));
		assertTrue(contact.getPhone().equals("0123456789"));
		assertTrue(contact.getAddress().equals("address"));
	}
	
	@Test
	void testContactInvalidId() {
		
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Contact ("12345678910", "first", "last", "0123456789", "address");
		});
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Contact (null, "first", "last", "0123456789", "address");
		});	
	}

	
	@Test
	void testContactInvalidFirstName() {
		

		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Contact ("0", "jeseniataliaurbinaroberts", "last", "0123456789", "address");
		});
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Contact ("0", null, "last", "0123456789", "address");
		});	
	
	}
	
	@Test
	void testContactInvalidLastName() {

		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Contact ("0", "first", "jeseniataliaurbinaroberts", "0123456789", "address");
		});
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Contact ("0", "first", null , "0123456789", "address");
		});
	}
	
	@Test
	void testContactInvalidPhoneNumber() {
		
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Contact ("0", "first", "last", "012345678", "address");
		});
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Contact ("0", "first", "last" , null , "address");
		});
	}

	
	@Test
	void testContactInvalidAddress() {

		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Contact ("0", "first", "last", "0123456789", "202 VeryLongAddressThatWillCauseAnError Drive");
		});
		Assertions.assertThrows(IllegalArgumentException.class, () -> {
			new Contact ("0", "first", "last" ,"0123456789" , null);
		});
		
	}


}
