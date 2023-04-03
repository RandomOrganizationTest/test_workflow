################################
Functional tests
################################

Test: test_good_request
====

Params:
    - uuid: f3ec5f99-7082-47e0-b954-e6a4376bb2c5

Response:
    - status: 200

.. code-block:: json

    {
        "success": {
            "group": "d471ee6f-e4da-4581-aa15-435f96c658f1",
            "deliveries": [
                "2bf39929-757c-4fea-9332-fb8343bb7a9c",
                "fa27530e-9b11-44ca-b485-0bf8b9fadb5b"
            ]
        }
    }

- [X] TEST PASSED

Test: test_empty
====

Params:
    - id: b904878a-b32d-4ede-88d2-4e755370aedc

Response:
    - status: 200

.. code-block:: json

    {
        "success": {
            "group": "bfd47922-bf37-45ef-b5a6-9ebdadb42b89",
            "deliveries": []
        }
    }

- [X] TEST PASSED

Test: test_bad_value
====

Params:
    - id: f3ec5f99-7082-47e0-b954-e6a4376bb2c5A

Response:
    - status: 404

.. code-block:: json

    {
        "error": {
            "internal": "order_not_found",
            "details": "order with UUID f3ec5f99-7082-47e0-b954-e6a4376bb2c5A not found"
        }
    }

- [X] TEST PASSED