-module(oceair).
-export([on_client_connected/1]).
-export([on_client_disconnected/2]).
-export([on_client_subscribe/3]).
-export([on_client_unsubscribe/3]).
-export([on_message_publish/1]).
-export([on_message_delivered/3]).
-export([on_message_acked/3]).
-on_load(load_nif_so/0).

load_nif_so() ->
    erlang:load_nif("/opt/pros/erlang/emq-relx/deps/emq_oceair/src/oceair/liboceair", 0).

on_client_connected(ClientId) ->
    io:format("nif not loaded"),
    ok.

on_client_disconnected(ClientId, Reason) ->
    io:format("nif not loaded"),
    ok.

on_client_subscribe(ClientId, Username, TopicTable) ->
    io:format("nif not loaded"),
    ok.

on_client_unsubscribe(ClientId, Username, TopicTable) ->
    io:format("nif not loaded"),
    ok.

on_message_publish(Message) ->
    io:format("nif not loaded"),
    Message.

on_message_delivered(ClientId, Username, Message) ->
    io:format("nif not loaded"),
    ok.

on_message_acked(ClientId, Username, Message) ->
    io:format("nif not loaded"),
    ok.



