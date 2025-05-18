1. to make a page searchable:

    1. finish the html and css
    2. add in `views.py`: 
        ```
        def post_products(request):
            return render(request, 'goods/post_products.html')
        ```

    3. add url route in `urls.py`
        ```
        urlpatterns = [
            # ...
            url(r'post_products/$', views.post_products name='post_products'),
        ]
        ```