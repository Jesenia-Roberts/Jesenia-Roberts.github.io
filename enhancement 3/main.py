# File: main.py
# Author: Jesenia Roberts
# Date: 8/9/2024
# Description: Runs the dashboard
from contact_service import ContactService
from mongodb_client import MongoDbClient
import dash
from dash import dcc, html
from dash.dependencies import Input, Output, State
import dash_table
import pandas as pd

print("Initializing mongodb client")
# Create the mongodb client that connects to the contacts db
client = MongoDbClient()

# Create the contact service that
print("Creating contact service")
contact_service = ContactService(client)

print("Retrieving contacts")
contacts = contact_service.get_all_contacts()

# Create DataFrame
print("Creating DataFrame from contacts")
contacts_list = []
for contact in contacts:
    contacts_list.append(contact.__dict__)

df = pd.DataFrame(contacts_list)

# Initialize the Dash app
app = dash.Dash(__name__)

# Layout of the app
app.layout = html.Div([
    dash_table.DataTable(
        id='table',
        columns=[{"name": i, "id": i} for i in df.columns],
        data=df.to_dict('records'),
        editable=True
    ),
    html.Div([
        dcc.Input(id='input-first-name', type='text', placeholder='First Name'),
        dcc.Input(id='input-last-name', type='text', placeholder='Last Name'),
        dcc.Input(id='input-phone', type='text', placeholder='Phone'),
        dcc.Input(id='input-address', type='text', placeholder='Address'),
        html.Button('Add Contact', id='add-row-button', n_clicks=0)
    ]),
    html.Div([
        dcc.Input(id='input-edit-contact-id', type='text', placeholder='Contact ID'),
        dcc.Input(id='input-edit-first-name', type='text', placeholder='First Name'),
        dcc.Input(id='input-edit-last-name', type='text', placeholder='Last Name'),
        dcc.Input(id='input-edit-phone', type='text', placeholder='Phone'),
        dcc.Input(id='input-edit-address', type='text', placeholder='Address'),
        html.Button('Edit Contact', id='edit-row-button', n_clicks=0)
    ]),
    html.Div(id='output')
])


# Callback to add a new row
@app.callback(
    Output('table', 'data', allow_duplicate=True),
    Input('add-row-button', 'n_clicks'),
    State('table', 'data'),
    State('table', 'columns'),
    State('input-first-name', 'value'),
    State('input-last-name', 'value'),
    State('input-phone', 'value'),
    State('input-address', 'value'),
    prevent_initial_call=True
)
def add_row(n_clicks, rows, columns, firstName, lastName, phone, address):
    if n_clicks > 0:
        contact_id = contact_service.add_contact(firstName, lastName, phone, address)
        rows.append(
            {'contactID': contact_id,
             'firstName': firstName,
             'lastName': lastName,
             'phone': phone,
             'address': address}
        )
    return rows


# Callback to edit a row
@app.callback(
    Output('table', 'data'),
    Input('edit-row-button', 'n_clicks'),
    State('table', 'data'),
    State('table', 'columns'),
    State('input-edit-contact-id', 'value'),
    State('input-edit-first-name', 'value'),
    State('input-edit-last-name', 'value'),
    State('input-edit-phone', 'value'),
    State('input-edit-address', 'value')
)
def add_row(n_clicks, rows, columns, contactID, firstName, lastName, phone, address):
    if n_clicks > 0:
        if contact_service.get_contact_by_id(contactID) is not None:
            contact_service.update_first(contactID, firstName)
            contact_service.update_last(contactID, lastName)
            contact_service.update_phone_number(contactID, phone)
            contact_service.update_address(contactID, address)

            # Function to find the index of a dictionary with a specific key-value pair
            index = next((index for index, d in enumerate(rows) if d.get('contactID') == contactID), None)
            rows[index] = {
                'contactID': contactID,
                'firstName': firstName,
                'lastName': lastName,
                'phone': phone,
                'address': address
            }
    return rows


# Run the app
if __name__ == '__main__':
    app.run_server(debug=True)

