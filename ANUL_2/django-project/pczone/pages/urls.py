from django.urls import path, include

from .views import home, info, log, about,contact, cart
urlpatterns = [
    path('', home, name="home"),
    path('info', info, name = "info"),
    path('log', log, name = "log"),
    path('about', about, name = "about"),
    path('contact', contact, name = "contact"),
    path('cart', cart, name = "cart"),
    path('products', include("produse.urls"))
]
