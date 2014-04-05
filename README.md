# mruby-cmigemo

## Requirements
* C/Migemo

## Example
```ruby
m = nil

puts ("enable:" + Migemo.migemo_is_enable(m).to_s)

m = Migemo.migemo_open("E:/bin/dict/han2zen.dat")

puts ("enable:" + Migemo.migemo_is_enable(m).to_s)

Migemo.migemo_set_operator(m, Migemo::MIGEMO_OPINDEX_OR,       '\|')
Migemo.migemo_set_operator(m, Migemo::MIGEMO_OPINDEX_NEST_IN,  '\(')
Migemo.migemo_set_operator(m, Migemo::MIGEMO_OPINDEX_NEST_OUT, '\)')
puts Migemo.migemo_get_operator(m, Migemo::MIGEMO_OPINDEX_OR)
puts Migemo.migemo_get_operator(m, Migemo::MIGEMO_OPINDEX_NEST_IN)
puts Migemo.migemo_get_operator(m, Migemo::MIGEMO_OPINDEX_NEST_OUT)

puts Migemo.migemo_query(m, "KoreHaTesutoMesse-jiDesu")

Migemo.migemo_load(m, Migemo::MIGEMO_DICTID_MIGEMO, "E:/bin/dict/migemo-dict")

puts Migemo.migemo_query(m, "KoreHaTesutoMesse-jiDesu")

Migemo.migemo_close(m)
```
