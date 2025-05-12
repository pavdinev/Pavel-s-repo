from django.shortcuts import render
import random
from faker import Faker

fake = Faker()

def index(request):
    message = ''
    if request.method == 'POST':
        message = 'Hello'
    return render(request, 'myapp/index.html', {'message': message})

def table_view(request):
    sort_by = request.GET.get('sort_by', '')
    data = [(fake.first_name(), random.randint(18, 80)) for _ in range(100)]

    if sort_by == 'name':
        data.sort(key=lambda x: x[0])
    elif sort_by == 'age':
        data.sort(key=lambda x: x[1])

    return render(request, 'myapp/table.html', {'data': data, 'sort_by': sort_by})
