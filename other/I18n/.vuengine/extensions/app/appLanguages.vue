<template>
	<div>

		<b-form>

			<b-form-group>
				<b-table
					striped
					hover
					:items="data.config.project.i18n.languages"
					:fields="formFields"
					primary-key="id"
					sort-by="id"
					sort-desc
					foot-clone
					show-empty
					:class="[{changed: JSON.stringify(data.config.project.i18n.languages) !== JSON.stringify(data.lastSavedConfig.project.i18n.languages)}]"
				>
					<template slot="empty" slot-scope="scope">
						No languages defined
					</template>
					<template slot="id" slot-scope="row">
						<b-form-input
							v-model="row.item.id"
							type="text"
							min="1"
							required
						></b-form-input>
					</template>
					<template slot="name" slot-scope="row">
						<b-form-input
							v-model="row.item.name"
							type="text"
							min="1"
							required
						></b-form-input>
					</template>
					<template slot="flag" slot-scope="row">
						<b-form-input
							v-model="row.item.flag"
							type="text"
						></b-form-input>
					</template>
					<template slot="actions" slot-scope="row">
						<b-button size="sm" pill @click="removeEntry(row.item)">Remove</b-button>
					</template>
					<template slot="FOOT_id">
						<b-form-input
							ref="newEntryId"
							type="text"
							min="1"
							required
						></b-form-input>
					</template>
					<template slot="FOOT_name">
						<b-form-input
							ref="newEntryName"
							type="text"
							min="1"
							required
						></b-form-input>
					</template>
					<template slot="FOOT_flag">
						<b-form-input
							ref="newEntryFlag"
							type="text"
						></b-form-input>
					</template>
					<template slot="FOOT_actions">
						<b-button size="sm" pill @click="addEntry()">Add</b-button>
					</template>
				</b-table>
			</b-form-group>

		</b-form>


	</div>
</template>

<script>
	module.exports = {
		props: [
			'data',
			'i18n'
		],
		data() {
			return {
				formFields: [
					{
						key: 'id',
						label: 'ID'
					},
					{
						key: 'name',
						label: 'Name'
					},
					{
						key: 'flag',
						label: 'Flag Entity'
					},
					{
						key: 'actions',
						label: '',
						class: 'text-right'
					}
				],
			}
		},
		methods: {
			addEntry() {
				let id = this.$refs.newEntryId.localValue;
				let name = this.$refs.newEntryName.localValue;
				let flag = this.$refs.newEntryFlag.localValue;

				this.$refs.newEntryId.state = (!id || this.data.config.project.i18n.languages.filter(obj => {return obj.id === id}).length) ? 'invalid' : null;
				this.$refs.newEntryName.state = (!name) ? 'invalid': null;

				if (this.$refs.newEntryId.state !== 'invalid' && this.$refs.newEntryName.state !== 'invalid') {
					this.data.config.project.i18n.languages.push({
						'id': id,
						'name': name,
						'flag': flag
					});
					this.data.config.project.i18n.languages.sort(function (a,b) {
						if (b.id > a.id) return 1;
						else if (b.id < a.id) return -1;
						else return 0;
					});

					this.$refs.newEntryId.localValue = undefined;
					this.$refs.newEntryName.localValue = undefined;
					this.$refs.newEntryFlag.localValue = undefined;
				}

			},
			removeEntry(item) {
				Vue.delete(this.data.config.project.i18n.languages, this.data.config.project.i18n.languages.indexOf(item));
			}
		}
	}
</script>

<style scoped>
</style>