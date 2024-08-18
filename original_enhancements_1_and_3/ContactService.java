// REVIEW: ADD HEADER COMMENT 
package module_3_milestone;

import java.util.HashMap;
import java.util.Map;

public class ContactService {

	private Map<String, Contact> contactList;
	private int next_id; // REVIEW: CHANGE THIS VARIABLE NAME TO CAMELCASE
	
	// REVIEW: ADD DESCRIPTION FOR METHODS AND PARAMETERS
	public ContactService() {
		// REVIEW: CHANGE ID SYSTEM TO CREATE RANDOMIZED IDS
		next_id = 1;
		contactList = new HashMap <String, Contact>();
	}
	
	public void addContact() {
		Contact contact = new Contact(next_id + "", "", "", "0000000000", "");
		contactList.put(next_id + "", contact);
		next_id ++;
	}
	
	public void deleteContact(String contactId) {
		// REVIEW: INCLUDE ERROR MESSAGES FOR IF CONTACT ID DOES NOT EXIST
		contactList.remove(contactId);
	}
	
	public void updateFirst(String contactId, String first) {
		if(contactList.containsKey(contactId)) {
			contactList.get(contactId).setFirstName(first);
		}
	}
	
	public void updateLast(String contactId, String last) {
		if(contactList.containsKey(contactId)) {
			contactList.get(contactId).setLastName(last);
		}
	}
	
	public void updatePhoneNumber(String contactId, String phoneNumber) {
		if(contactList.containsKey(contactId)) {
			contactList.get(contactId).setPhone(phoneNumber);
		}
	}
	
	public void updateAddress(String contactId, String address) {
		if(contactList.containsKey(contactId)) {
			contactList.get(contactId).setAddress(address);
		}
	}
	
	public Contact getContactById(String contactId) {
		return contactList.get(contactId);
	}
}
