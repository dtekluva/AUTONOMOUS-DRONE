from django.shortcuts import render
import channels.layers
from asgiref.sync import async_to_sync
from channels.layers import get_channel_layer
from django.http import HttpResponse
from main.models import Trigger

def update(request, trigger_code):

    print(trigger_code)
    target_trigger = Trigger.objects.get(code = trigger_code)
    target_trigger.is_triggered = True
    target_trigger.save()

    create_alert(trigger_code)

    return HttpResponse('<p>Done</p>')

def create_alert(trigger_code):

    channel_layer = get_channel_layer()

    async_to_sync(channel_layer.group_send)(
        'chat_%s' %'alerts',
        {
            'type': 'chat_message',
            'message': trigger_code
        }
    )

def index(request):
    Trigger.objects.update(is_triggered = False)
    return render(request, 'index.html')
