import random
import pytest
import csv


class Data:
    def __init__(self):
        self.customers = []
        self.customers_spent = {}

        self.products = []
        self.product_amount = {}
        self.product_gross = {}

        self.orders = []


@pytest.fixture(autouse=True)
def data(paths, fake):
    data = Data()

    for i in range(random.randint(5, 10)):
        data.customers.append({
            'id': i + 1,
            'name': fake.name(),
            'address': fake.street_address()
        })

        data.customers_spent[i + 1] = 0

    for i in range(random.randint(5, 10)):
        data.products.append({
            'id': i + 1,
            'name': fake.word(),
            'price': random.randint(1, 100)
        })

        data.product_amount[i + 1] = 0
        data.product_gross[i + 1] = 0

    for i in range(random.randint(50, 100)):
        customer_id = random.randint(1, len(data.customers))
        product_id = random.randint(1, len(data.products))

        data.orders.append({
            'id': i + 1,
            'customerid': customer_id,
            'productid': product_id,
            'amount': random.randint(1, 15)
        })

        data.product_amount[product_id] += data.orders[-1]['amount']
        data.product_gross[product_id] += data.orders[-1]['amount'] * data.products[product_id - 1]['price']
        data.customers_spent[customer_id] += data.orders[-1]['amount'] * data.products[product_id - 1]['price']

    data_sets = [(data.customers, 'customers.csv'), (data.products, 'products.csv'), (data.orders, 'orders.csv')]
    for data_set, file in data_sets:
        with open(file, 'w', newline='') as csv_file:
            writer = csv.DictWriter(csv_file, quoting=csv.QUOTE_NONNUMERIC, fieldnames=data_set[0])
            writer.writeheader()
            writer.writerows(data_set)

    return data


class TestAssignment41:
    def test_customers(self, app, data):
        app.check([], [f'Customer: {customer["name"]}, {customer["address"]}' for customer in data.customers])

    def test_products(self, app, data):
        app.check([], [f'Product: {product["name"]}, {product["price"]}' for product in data.products])

    def test_products_amount(self, app, data):
        app.check([], [f'{product["name"]} amount: {data.product_amount[product["id"]]}' for product in data.products])

    def test_products_gross(self, app, data):
        app.check([], [f'{product["name"]} gross income: {data.product_gross[product["id"]]}'
                       for product in data.products])

    def test_money_spent(self, app, data):
        app.check([], [f'{customer["name"]} money spent: {data.customers_spent[customer["id"]]}'
                       for customer in data.customers])
