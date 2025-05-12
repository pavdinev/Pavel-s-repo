import graphene
from graphene_django.types import DjangoObjectType
from .models import Product

# Define a Graphene type for the Product model
class ProductType(DjangoObjectType):
    class Meta:
        model = Product

# Create a query to fetch products
class Query(graphene.ObjectType):
    products = graphene.List(ProductType)

    def resolve_products(self, info):
        return Product.objects.all()

# Define the schema
schema = graphene.Schema(query=Query)