





event happens
->
the keycallback captures it
->
we create an event struct from the event that is queued in the orchestrator
->
this event orchestrator has a vector of handlers, these handlers define an Event type that they want to listen to
->
the orchestrator selects all handlers that match with the event type that was listened to
->
a function .exec on each handler is called in order so all event handlers for the events that were captured in that frame are run using the flush() function

---

3. Unregister during flush is dangerous
If a handler's .exec() calls unregister() on another handler (or itself), you're modifying the vector while iterating it. Classic invalidation bug. Fix: either flag handlers as "pending removal" and clean up after the flush loop, or iterate over a copy.

4. Handler identity for unregister
How does unregister() find the right handler? By pointer? By ID? You need a stable identifier. A simple incrementing uint32_t id assigned at registration works well.

---

we need register() and unregister() functions in the event handlers, which will indicate when they will be listing to events, for example, we maintain the
jump event handler as long as the bird is alive
