from django.shortcuts import render
import channels.layers
from asgiref.sync import async_to_sync
from channels.layers import get_channel_layer
from django.http import HttpResponse


def ping(request):
    channel_layer = get_channel_layer()

    async_to_sync(channel_layer.group_send)(
        'chat_%s' %'alerts',
        {
            'type': 'chat_message',
            'message': 'Trespass noted'
        }
    )
    return HttpResponse('<p>Done</p>')

def index(request):
    ping(request)
    return render(request, 'chat/index.html', {})

def home(request):
    ping(request)
    return render(request, 'chat/index.html', {})

def room(request, room_name):
    return render(request, 'chat/room.html', {
        'room_name': room_name
    })
