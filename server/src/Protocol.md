#Protocol Documentation
##Introduction
The protocol is designed to facilitate the exchange of messages between different components or entities within a system. It employs serialization and deserialization to represent data in a format that can be sent as bytes, allowing for the reconstruction of the original data.

##Message Structure
Each message is structured as a string that consists of elements and delimiters. The elements are specific pieces of information or data, and the delimiters are used to separate these elements.

##Message Types
The protocol supports various message types, including:

Data: Contains data information.
Action: Represents an action.
Ready: Signifies readiness.
Go: Begins the game.
Connect: Establishes a connection.

##Serialization
The serialization function converts data into a serialized string for transmission. The serialized string is structured as follows:

<messageType-subElement1.subElement2.subElementN_Element2>
message_type is a string that specifies the type of message (e.g., "data", "action", "ready", "go", "connect").
subElement 1, 2, N represent different parts of the first element, separated by ".".
_ serves as the delimiter between elements.
For example, a serialized "Data" message might look like this:

data-1.15.7_3.38.0\_2.4.3

that string is then converted to a vector of bytes (uint8_t) for transmission

##Deserialization
The deserialization function interprets the serialized string to reconstruct the original data. It identifies the message type and extracts the relevant elements and their values.

For instance, deserializing the string data-1.15.7_3.38.0\_2.4.3 would result in a message of type "Data" with the following values:

Element 1: 1.15.7
Element 2: 3.38.0
Element 3: 2.4.3